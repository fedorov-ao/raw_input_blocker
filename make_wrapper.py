#!/usr/bin/python

import sys
import re
import getopt

reMacro = re.compile(" *(?P<ret>(#if|#endif).+)")
reDef = re.compile("(?P<ret>[^ ]+) *(?P<cconv>WINAPI) *(?P<name>[^ ]+) *\( *(?P<args>[^\)]*) *\);?")

def parse_match(m):
  r = None
  if m is None:
    return r
  ret = m.group("ret")
  r = { "ret" : ret }
  if ret[0] == "#":
    return r
  for k in ("cconv", "name"):
    r[k] = m.group(k)
  args = m.group("args")
  if args is not None:
    args = re.sub("( |\t){2,}", " ", args)
    args = args.replace("\n", " ").split(",")
    args2 = []
    for arg in args:
      arg = arg.strip(" ").strip("\t")
      for c in ("*", " ", "\t"):
        i = arg.rfind(c)
        if i != -1:
          i += 1
          t, n = arg[:i].strip(" "), arg[i:].strip(" ")
          args2.append([t, n])
          break
      else:
        args2.append([arg])
    args = args2
  r["args"] = args
  r["def"] = m.group(0).replace("\n", " ")
  return r


def parse_def(s):
  m = reMacro.search(s)
  if m is None:
    m = reDef.search(s)
  return parse_match(m)


def make_args(args):
  def g(args):
    for arg in args:
      yield " ".join(arg)
  args = ", ".join(g(args))
  return args.strip(" ")


def macro_decorator(wrapped):
  def func(d, *args, **kwargs):
    ret = d["ret"]
    if ret[0] == "#":
      return ret
    else:
      return wrapped(d, *args, **kwargs)
  return func


DT_FUNC = 0
DT_FUNC_PTR = 1
DT_FUNC_PTR_DECLTYPE = 2
DT_DEF = 3

@macro_decorator
def make_def(d, defType, addSemicolon=True):
  if type(d) is dict and d.get("cconv") == "WINAPI":
    if defType == DT_DEF:
      return d
    args = make_args(d["args"])
    fmt = {
      DT_FUNC : "DLLEXPORT {ret} {cconv} {name} ({args}){suffix}",
      DT_FUNC_PTR : "{ret} {cconv} (*{name}) ({args}){suffix}",
      DT_FUNC_PTR_DECLTYPE : "decltype(::{name}) * {name}{suffix}"
    }[defType]
    return fmt.format(ret=d["ret"], cconv=d["cconv"], name=d["name"], args=args, suffix=";" if addSemicolon else "")
  else:
    return "//" + str(d)


@macro_decorator
def make_func(d, prefix):
  args = d["args"]
  j = 0
  for i in range(len(args)):
    arg = args[i]
    if len(arg) == 1:
      argName = ""
      if arg[0] == "...":
        pass
      elif arg[0].upper() != "VOID":
        argName = "arg{}".format(j)
        j += 1
      args[i] = [arg[0], argName]
  decl = make_def(d, DT_FUNC, False)
  returnStatement = "return " if d["ret"].upper() != "VOID" else ""
  def make_arg_name(arg):
    return { "VOID" : "", "..." : "arglist" }.get(arg[0], arg[1])
  argNames = ", ".join(make_arg_name(arg) for arg in args)
  fmt = "\n{{\n  {ret}{prefix}{name}({argNames});\n}}\n"
  decl += fmt.format(ret=returnStatement, prefix=prefix, name=d["name"], argNames=argNames)
  return decl


@macro_decorator
def make_import_init(d, prefix):
  name = d["name"]
  prefixedName = prefix + name
  return '{prefixedName} = reinterpret_cast<decltype({prefixedName})>(GetProcAddress(hModule,"{name}"));'.format(prefixedName=prefixedName, name=name)


def parse_seq(seq, includeUnparsed=True):
  defs = []
  for l in seq:
    l = l.strip("\n")
    def_ = parse_def(l)
    if def_ is None:
      if includeUnparsed:
        def_ = l
      else:
        continue
    defs.append(def_)
  return defs


def parse_seq2(seq):
  def worker(seq):
    all_ = " ".join(seq)
    all_ = re.sub("DECLSPEC_HOTPATCH", "", all_)
    all_ = re.sub("/\*.*?\* */", "", all_)
    matches = []
    i = 0
    while True:
      m = reDef.search(all_, i)
      if m is None:
        break
      matches.append(m)
      i = m.end()
    defs = []
    for m in matches:
      def_ = parse_match(m)
      if def_ is None:
        continue
      defs.append(def_)
    return defs
  defs, subseq = [], []
  for s in seq:
    m = reMacro.match(s)
    if m is not None:
      defs.extend(worker(subseq))
      subseq = []
      #defs.append({"ret" : m.group("ret")})
    else:
      subseq.append(s)
  if len(subseq) != 0:
    defs.extend(worker(subseq))
  return defs


def run():
  mode = sys.argv[1]
  if mode == "check_missing":
    defsFileName, symFileName = sys.argv[2], sys.argv[3]
    with open(defsFileName) as defsFile, open(symFileName) as symFile:
      defs = set(d["name"] for d in parse_seq2(defsFile))
      sym = set(sym.strip(" ").strip("\n") for sym in symFile)
      for l in sorted(list(sym - defs)):
        print l
  elif mode == "check_missing2":
    lessFileName, moreFileName = sys.argv[2], sys.argv[3]
    with open(lessFileName) as lessFile, open(moreFileName) as moreFile:
      less, more = parse_seq2(lessFile), parse_seq2(moreFile)
      less = { d["name"] : d for d in less }
      more = { d["name"] : d for d in more }
      diff = set(more.keys()) - set(less.keys())
      for d in diff:
        print more[d]["def"]
  else:
    import glob
    path = sys.argv[2]
    defs = []
    for fname in glob.glob(path):
      with open(fname) as f:
        defs.extend(parse_seq2(f))
    modes = mode.split(",")
    l = len(modes)
    li = l - 1
    for i in range(l):
      mode = modes[i]
      if mode in ("func_ptrs_decltype", "func_ptrs", "func_decls", "defs"):
        defType = {
          "func_ptrs_decltype" : DT_FUNC_PTR_DECLTYPE,
          "func_ptrs" : DT_FUNC_PTR,
          "func_decls" : DT_FUNC,
          "defs" : DT_DEF
        }.get(mode, None)
        for d in defs:
          #print "//" + d if type(d) is str else make_def(d, defType, True)
          print make_def(d, defType, True)
      elif mode == "funcs":
        prefix = sys.argv[3]
        for d in defs:
          print make_func(d, prefix)
      elif mode == "import_inits":
        prefix = sys.argv[3]
        for d in defs:
          print make_import_init(d, prefix)
      if i != li: print "\n\n"
      


import unittest
class ParseDefTestCase(unittest.TestCase):
  def test_basic_def(self):
    s = "WINUSERAPI int WINAPI GetMouseMovePointsEx(UINT cbSize,LPMOUSEMOVEPOINT lppt,LPMOUSEMOVEPOINT lpptBuf,int nBufPoints,DWORD resolution);"
    d = {'args': [['UINT', 'cbSize'], ['LPMOUSEMOVEPOINT', 'lppt'], ['LPMOUSEMOVEPOINT', 'lpptBuf'], ['int', 'nBufPoints'], ['DWORD', 'resolution']], 'cconv': 'WINAPI', 'name': 'GetMouseMovePointsEx', 'ret': 'int'}
    self.assertEqual(d, parse_def(s))

  def test_arg_ptr_def(self):
    s = "WINUSERAPI int WINAPI ToUnicodeEx(UINT wVirtKey,UINT wScanCode,CONST BYTE *lpKeyState,LPWSTR pwszBuff,int cchBuff,UINT wFlags,HKL dwhkl);"
    d = {'args': [['UINT', 'wVirtKey'], ['UINT', 'wScanCode'], ['CONST BYTE *', 'lpKeyState'], ['LPWSTR', 'pwszBuff'], ['int', 'cchBuff'], ['UINT', 'wFlags'], ['HKL', 'dwhkl']], 'cconv': 'WINAPI', 'name': 'ToUnicodeEx', 'ret': 'int'}
    self.assertEqual(d, parse_def(s))
  
  def test_ellipsis_arg(self):
    s = "WINUSERAPI int WINAPIV wsprintfA(LPSTR,LPCSTR,...);"
    d = {'args': ['LPSTR', 'LPCSTR', '...'], 'cconv': 'WINAPIV', 'name': 'wsprintfA', 'ret': 'int'}
    self.assertEqual(d, parse_def(s))

  def test_space_after_name(self):
    s = 'WINUSERAPI WINBOOL WINAPI GetGestureConfig (HWND hwnd, DWORD dwReserved, DWORD dwFlags, PUINT pcIDs, PGESTURECONFIG pGestureConfig, UINT cbSize);'
    d = {'args': [['HWND', 'hwnd'], ['DWORD', 'dwReserved'], ['DWORD', 'dwFlags'], ['PUINT', 'pcIDs'], ['PGESTURECONFIG', 'pGestureConfig'], ['UINT', 'cbSize']], 'cconv': 'WINAPI', 'name': 'GetGestureConfig', 'ret': 'WINBOOL'}
    self.assertEqual(d, parse_def(s))


if __name__ == "__main__":
  if len(sys.argv) == 1:
    unittest.main()
  else:
    run()
