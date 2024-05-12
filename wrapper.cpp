#include "wrapper.hpp"
#include "logging.hpp"
#include <cstdarg>
#include <string>
#include <stdexcept>
#include <fstream>

#define _WIN32_WINNT 0x0602
#define _USER32_
#undef STRICT

#include <windows.h>

#define DLLEXPORT __declspec(dllexport)

struct User32
{
  decltype(wvsprintfA) * wvsprintfA;
  decltype(wvsprintfW) * wvsprintfW;
  decltype(wsprintfA) * wsprintfA;
  decltype(wsprintfW) * wsprintfW;
  decltype(LoadKeyboardLayoutA) * LoadKeyboardLayoutA;
  decltype(LoadKeyboardLayoutW) * LoadKeyboardLayoutW;
  decltype(ActivateKeyboardLayout) * ActivateKeyboardLayout;
  decltype(ToUnicodeEx) * ToUnicodeEx;
  decltype(UnloadKeyboardLayout) * UnloadKeyboardLayout;
  decltype(GetKeyboardLayoutNameA) * GetKeyboardLayoutNameA;
  decltype(GetKeyboardLayoutNameW) * GetKeyboardLayoutNameW;
  decltype(GetKeyboardLayoutList) * GetKeyboardLayoutList;
  decltype(GetKeyboardLayout) * GetKeyboardLayout;
  decltype(GetMouseMovePointsEx) * GetMouseMovePointsEx;
  decltype(CreateDesktopA) * CreateDesktopA;
  decltype(CreateDesktopW) * CreateDesktopW;
  decltype(CreateDesktopExA) * CreateDesktopExA;
  decltype(CreateDesktopExW) * CreateDesktopExW;
  decltype(OpenDesktopA) * OpenDesktopA;
  decltype(OpenDesktopW) * OpenDesktopW;
  decltype(OpenInputDesktop) * OpenInputDesktop;
  decltype(EnumDesktopsA) * EnumDesktopsA;
  decltype(EnumDesktopsW) * EnumDesktopsW;
  decltype(EnumDesktopWindows) * EnumDesktopWindows;
  decltype(SwitchDesktop) * SwitchDesktop;
  decltype(SetThreadDesktop) * SetThreadDesktop;
  decltype(CloseDesktop) * CloseDesktop;
  decltype(GetThreadDesktop) * GetThreadDesktop;
  decltype(CreateWindowStationA) * CreateWindowStationA;
  decltype(CreateWindowStationW) * CreateWindowStationW;
  decltype(OpenWindowStationA) * OpenWindowStationA;
  decltype(OpenWindowStationW) * OpenWindowStationW;
  decltype(EnumWindowStationsA) * EnumWindowStationsA;
  decltype(EnumWindowStationsW) * EnumWindowStationsW;
  decltype(CloseWindowStation) * CloseWindowStation;
  decltype(SetProcessWindowStation) * SetProcessWindowStation;
  decltype(GetProcessWindowStation) * GetProcessWindowStation;
  decltype(SetUserObjectSecurity) * SetUserObjectSecurity;
  decltype(GetUserObjectSecurity) * GetUserObjectSecurity;
  decltype(GetUserObjectInformationA) * GetUserObjectInformationA;
  decltype(GetUserObjectInformationW) * GetUserObjectInformationW;
  decltype(SetUserObjectInformationA) * SetUserObjectInformationA;
  decltype(SetUserObjectInformationW) * SetUserObjectInformationW;
  decltype(IsHungAppWindow) * IsHungAppWindow;
  decltype(DisableProcessWindowsGhosting) * DisableProcessWindowsGhosting;
  decltype(RegisterWindowMessageA) * RegisterWindowMessageA;
  decltype(RegisterWindowMessageW) * RegisterWindowMessageW;
  decltype(TrackMouseEvent) * TrackMouseEvent;
  decltype(DrawEdge) * DrawEdge;
  decltype(DrawFrameControl) * DrawFrameControl;
  decltype(DrawCaption) * DrawCaption;
  decltype(DrawAnimatedRects) * DrawAnimatedRects;
  decltype(GetMessageA) * GetMessageA;
  decltype(GetMessageW) * GetMessageW;
  decltype(TranslateMessage) * TranslateMessage;
  decltype(DispatchMessageA) * DispatchMessageA;
  decltype(DispatchMessageW) * DispatchMessageW;
  decltype(SetMessageQueue) * SetMessageQueue;
  decltype(PeekMessageA) * PeekMessageA;
  decltype(PeekMessageW) * PeekMessageW;
  decltype(RegisterHotKey) * RegisterHotKey;
  decltype(UnregisterHotKey) * UnregisterHotKey;
  decltype(ExitWindowsEx) * ExitWindowsEx;
  decltype(SwapMouseButton) * SwapMouseButton;
  decltype(GetMessagePos) * GetMessagePos;
  decltype(GetMessageTime) * GetMessageTime;
  decltype(GetMessageExtraInfo) * GetMessageExtraInfo;
  decltype(GetUnpredictedMessagePos) * GetUnpredictedMessagePos;
  decltype(IsWow64Message) * IsWow64Message;
  decltype(SetMessageExtraInfo) * SetMessageExtraInfo;
  decltype(SendMessageA) * SendMessageA;
  decltype(SendMessageW) * SendMessageW;
  decltype(SendMessageTimeoutA) * SendMessageTimeoutA;
  decltype(SendMessageTimeoutW) * SendMessageTimeoutW;
  decltype(SendNotifyMessageA) * SendNotifyMessageA;
  decltype(SendNotifyMessageW) * SendNotifyMessageW;
  decltype(SendMessageCallbackA) * SendMessageCallbackA;
  decltype(SendMessageCallbackW) * SendMessageCallbackW;
  decltype(BroadcastSystemMessageExA) * BroadcastSystemMessageExA;
  decltype(BroadcastSystemMessageExW) * BroadcastSystemMessageExW;
  decltype(BroadcastSystemMessageA) * BroadcastSystemMessageA;
  decltype(BroadcastSystemMessageW) * BroadcastSystemMessageW;
  decltype(RegisterPowerSettingNotification) * RegisterPowerSettingNotification;
  decltype(UnregisterPowerSettingNotification) * UnregisterPowerSettingNotification;
  decltype(RegisterSuspendResumeNotification) * RegisterSuspendResumeNotification;
  decltype(UnregisterSuspendResumeNotification) * UnregisterSuspendResumeNotification;
  decltype(PostMessageA) * PostMessageA;
  decltype(PostMessageW) * PostMessageW;
  decltype(PostThreadMessageA) * PostThreadMessageA;
  decltype(PostThreadMessageW) * PostThreadMessageW;
  decltype(AttachThreadInput) * AttachThreadInput;
  decltype(ReplyMessage) * ReplyMessage;
  decltype(WaitMessage) * WaitMessage;
  decltype(WaitForInputIdle) * WaitForInputIdle;
  decltype(DefWindowProcA) * DefWindowProcA;
  decltype(DefWindowProcW) * DefWindowProcW;
  decltype(PostQuitMessage) * PostQuitMessage;
  decltype(InSendMessage) * InSendMessage;
  decltype(InSendMessageEx) * InSendMessageEx;
  decltype(GetDoubleClickTime) * GetDoubleClickTime;
  decltype(SetDoubleClickTime) * SetDoubleClickTime;
  decltype(RegisterClassA) * RegisterClassA;
  decltype(RegisterClassW) * RegisterClassW;
  decltype(UnregisterClassA) * UnregisterClassA;
  decltype(UnregisterClassW) * UnregisterClassW;
  decltype(GetClassInfoA) * GetClassInfoA;
  decltype(GetClassInfoW) * GetClassInfoW;
  decltype(RegisterClassExA) * RegisterClassExA;
  decltype(RegisterClassExW) * RegisterClassExW;
  decltype(GetClassInfoExA) * GetClassInfoExA;
  decltype(GetClassInfoExW) * GetClassInfoExW;
  decltype(CallWindowProcA) * CallWindowProcA;
  decltype(CallWindowProcW) * CallWindowProcW;
  decltype(RegisterDeviceNotificationA) * RegisterDeviceNotificationA;
  decltype(RegisterDeviceNotificationW) * RegisterDeviceNotificationW;
  decltype(UnregisterDeviceNotification) * UnregisterDeviceNotification;
  decltype(CreateWindowExA) * CreateWindowExA;
  decltype(CreateWindowExW) * CreateWindowExW;
  decltype(IsWindow) * IsWindow;
  decltype(IsMenu) * IsMenu;
  decltype(IsChild) * IsChild;
  decltype(DestroyWindow) * DestroyWindow;
  decltype(ShowWindow) * ShowWindow;
  decltype(AnimateWindow) * AnimateWindow;
  decltype(UpdateLayeredWindow) * UpdateLayeredWindow;
  decltype(UpdateLayeredWindowIndirect) * UpdateLayeredWindowIndirect;
  decltype(GetLayeredWindowAttributes) * GetLayeredWindowAttributes;
  decltype(PrintWindow) * PrintWindow;
  decltype(SetLayeredWindowAttributes) * SetLayeredWindowAttributes;
  decltype(ShowWindowAsync) * ShowWindowAsync;
  decltype(FlashWindow) * FlashWindow;
  decltype(FlashWindowEx) * FlashWindowEx;
  decltype(ShowOwnedPopups) * ShowOwnedPopups;
  decltype(OpenIcon) * OpenIcon;
  decltype(CloseWindow) * CloseWindow;
  decltype(MoveWindow) * MoveWindow;
  decltype(SetWindowPos) * SetWindowPos;
  decltype(GetWindowPlacement) * GetWindowPlacement;
  decltype(SetWindowPlacement) * SetWindowPlacement;
  decltype(GetWindowDisplayAffinity) * GetWindowDisplayAffinity;
  decltype(SetWindowDisplayAffinity) * SetWindowDisplayAffinity;
  decltype(BeginDeferWindowPos) * BeginDeferWindowPos;
  decltype(DeferWindowPos) * DeferWindowPos;
  decltype(EndDeferWindowPos) * EndDeferWindowPos;
  decltype(IsWindowVisible) * IsWindowVisible;
  decltype(IsIconic) * IsIconic;
  decltype(AnyPopup) * AnyPopup;
  decltype(BringWindowToTop) * BringWindowToTop;
  decltype(IsZoomed) * IsZoomed;
  decltype(CreateDialogParamA) * CreateDialogParamA;
  decltype(CreateDialogParamW) * CreateDialogParamW;
  decltype(CreateDialogIndirectParamA) * CreateDialogIndirectParamA;
  decltype(CreateDialogIndirectParamW) * CreateDialogIndirectParamW;
  decltype(DialogBoxParamA) * DialogBoxParamA;
  decltype(DialogBoxParamW) * DialogBoxParamW;
  decltype(DialogBoxIndirectParamA) * DialogBoxIndirectParamA;
  decltype(DialogBoxIndirectParamW) * DialogBoxIndirectParamW;
  decltype(EndDialog) * EndDialog;
  decltype(GetDlgItem) * GetDlgItem;
  decltype(SetDlgItemInt) * SetDlgItemInt;
  decltype(GetDlgItemInt) * GetDlgItemInt;
  decltype(SetDlgItemTextA) * SetDlgItemTextA;
  decltype(SetDlgItemTextW) * SetDlgItemTextW;
  decltype(GetDlgItemTextA) * GetDlgItemTextA;
  decltype(GetDlgItemTextW) * GetDlgItemTextW;
  decltype(CheckDlgButton) * CheckDlgButton;
  decltype(CheckRadioButton) * CheckRadioButton;
  decltype(IsDlgButtonChecked) * IsDlgButtonChecked;
  decltype(SendDlgItemMessageA) * SendDlgItemMessageA;
  decltype(SendDlgItemMessageW) * SendDlgItemMessageW;
  decltype(GetNextDlgGroupItem) * GetNextDlgGroupItem;
  decltype(GetNextDlgTabItem) * GetNextDlgTabItem;
  decltype(GetDlgCtrlID) * GetDlgCtrlID;
  decltype(GetDialogBaseUnits) * GetDialogBaseUnits;
  decltype(DefDlgProcA) * DefDlgProcA;
  decltype(DefDlgProcW) * DefDlgProcW;
  decltype(CallMsgFilterA) * CallMsgFilterA;
  decltype(CallMsgFilterW) * CallMsgFilterW;
  decltype(OpenClipboard) * OpenClipboard;
  decltype(CloseClipboard) * CloseClipboard;
  decltype(GetClipboardSequenceNumber) * GetClipboardSequenceNumber;
  decltype(GetClipboardOwner) * GetClipboardOwner;
  decltype(SetClipboardViewer) * SetClipboardViewer;
  decltype(GetClipboardViewer) * GetClipboardViewer;
  decltype(ChangeClipboardChain) * ChangeClipboardChain;
  decltype(SetClipboardData) * SetClipboardData;
  decltype(GetClipboardData) * GetClipboardData;
  decltype(RegisterClipboardFormatA) * RegisterClipboardFormatA;
  decltype(RegisterClipboardFormatW) * RegisterClipboardFormatW;
  decltype(CountClipboardFormats) * CountClipboardFormats;
  decltype(EnumClipboardFormats) * EnumClipboardFormats;
  decltype(GetClipboardFormatNameA) * GetClipboardFormatNameA;
  decltype(GetClipboardFormatNameW) * GetClipboardFormatNameW;
  decltype(EmptyClipboard) * EmptyClipboard;
  decltype(IsClipboardFormatAvailable) * IsClipboardFormatAvailable;
  decltype(GetPriorityClipboardFormat) * GetPriorityClipboardFormat;
  decltype(GetOpenClipboardWindow) * GetOpenClipboardWindow;
  decltype(AddClipboardFormatListener) * AddClipboardFormatListener;
  decltype(RemoveClipboardFormatListener) * RemoveClipboardFormatListener;
  decltype(GetUpdatedClipboardFormats) * GetUpdatedClipboardFormats;
  decltype(CharToOemA) * CharToOemA;
  decltype(CharToOemW) * CharToOemW;
  decltype(OemToCharA) * OemToCharA;
  decltype(OemToCharW) * OemToCharW;
  decltype(CharToOemBuffA) * CharToOemBuffA;
  decltype(CharToOemBuffW) * CharToOemBuffW;
  decltype(OemToCharBuffA) * OemToCharBuffA;
  decltype(OemToCharBuffW) * OemToCharBuffW;
  decltype(CharUpperA) * CharUpperA;
  decltype(CharUpperW) * CharUpperW;
  decltype(CharUpperBuffA) * CharUpperBuffA;
  decltype(CharUpperBuffW) * CharUpperBuffW;
  decltype(CharLowerA) * CharLowerA;
  decltype(CharLowerW) * CharLowerW;
  decltype(CharLowerBuffA) * CharLowerBuffA;
  decltype(CharLowerBuffW) * CharLowerBuffW;
  decltype(CharNextA) * CharNextA;
  decltype(CharNextW) * CharNextW;
  decltype(CharPrevA) * CharPrevA;
  decltype(CharPrevW) * CharPrevW;
  decltype(CharNextExA) * CharNextExA;
  decltype(CharPrevExA) * CharPrevExA;
  decltype(IsCharAlphaA) * IsCharAlphaA;
  decltype(IsCharAlphaW) * IsCharAlphaW;
  decltype(IsCharAlphaNumericA) * IsCharAlphaNumericA;
  decltype(IsCharAlphaNumericW) * IsCharAlphaNumericW;
  decltype(IsCharUpperA) * IsCharUpperA;
  decltype(IsCharUpperW) * IsCharUpperW;
  decltype(IsCharLowerA) * IsCharLowerA;
  decltype(IsCharLowerW) * IsCharLowerW;
  decltype(SetFocus) * SetFocus;
  decltype(GetActiveWindow) * GetActiveWindow;
  decltype(GetFocus) * GetFocus;
  decltype(GetKBCodePage) * GetKBCodePage;
  decltype(GetKeyState) * GetKeyState;
  decltype(GetAsyncKeyState) * GetAsyncKeyState;
  decltype(GetKeyboardState) * GetKeyboardState;
  decltype(SetKeyboardState) * SetKeyboardState;
  decltype(GetKeyNameTextA) * GetKeyNameTextA;
  decltype(GetKeyNameTextW) * GetKeyNameTextW;
  decltype(GetKeyboardType) * GetKeyboardType;
  decltype(ToAscii) * ToAscii;
  decltype(ToAsciiEx) * ToAsciiEx;
  decltype(ToUnicode) * ToUnicode;
  decltype(OemKeyScan) * OemKeyScan;
  decltype(VkKeyScanA) * VkKeyScanA;
  decltype(VkKeyScanW) * VkKeyScanW;
  decltype(VkKeyScanExA) * VkKeyScanExA;
  decltype(VkKeyScanExW) * VkKeyScanExW;
  decltype(keybd_event) * keybd_event;
  decltype(mouse_event) * mouse_event;
  decltype(SendInput) * SendInput;
  decltype(GetTouchInputInfo) * GetTouchInputInfo;
  decltype(CloseTouchInputHandle) * CloseTouchInputHandle;
  decltype(RegisterTouchWindow) * RegisterTouchWindow;
  decltype(UnregisterTouchWindow) * UnregisterTouchWindow;
  decltype(IsTouchWindow) * IsTouchWindow;
  decltype(InitializeTouchInjection) * InitializeTouchInjection;
  decltype(InjectTouchInput) * InjectTouchInput;
  decltype(GetPointerType) * GetPointerType;
  decltype(GetPointerCursorId) * GetPointerCursorId;
  decltype(GetPointerInfo) * GetPointerInfo;
  decltype(GetPointerInfoHistory) * GetPointerInfoHistory;
  decltype(GetPointerFrameInfo) * GetPointerFrameInfo;
  decltype(GetPointerFrameInfoHistory) * GetPointerFrameInfoHistory;
  decltype(GetPointerTouchInfo) * GetPointerTouchInfo;
  decltype(GetPointerTouchInfoHistory) * GetPointerTouchInfoHistory;
  decltype(GetPointerFrameTouchInfo) * GetPointerFrameTouchInfo;
  decltype(GetPointerFrameTouchInfoHistory) * GetPointerFrameTouchInfoHistory;
  decltype(GetPointerPenInfo) * GetPointerPenInfo;
  decltype(GetPointerPenInfoHistory) * GetPointerPenInfoHistory;
  decltype(GetPointerFramePenInfo) * GetPointerFramePenInfo;
  decltype(GetPointerFramePenInfoHistory) * GetPointerFramePenInfoHistory;
  decltype(SkipPointerFrameMessages) * SkipPointerFrameMessages;
  decltype(RegisterPointerInputTarget) * RegisterPointerInputTarget;
  decltype(UnregisterPointerInputTarget) * UnregisterPointerInputTarget;
  decltype(EnableMouseInPointer) * EnableMouseInPointer;
  decltype(IsMouseInPointerEnabled) * IsMouseInPointerEnabled;
  decltype(RegisterTouchHitTestingWindow) * RegisterTouchHitTestingWindow;
  decltype(EvaluateProximityToRect) * EvaluateProximityToRect;
  decltype(EvaluateProximityToPolygon) * EvaluateProximityToPolygon;
  decltype(PackTouchHitTestingProximityEvaluation) * PackTouchHitTestingProximityEvaluation;
  decltype(GetWindowFeedbackSetting) * GetWindowFeedbackSetting;
  decltype(SetWindowFeedbackSetting) * SetWindowFeedbackSetting;
  decltype(GetLastInputInfo) * GetLastInputInfo;
  decltype(MapVirtualKeyA) * MapVirtualKeyA;
  decltype(MapVirtualKeyW) * MapVirtualKeyW;
  decltype(MapVirtualKeyExA) * MapVirtualKeyExA;
  decltype(MapVirtualKeyExW) * MapVirtualKeyExW;
  decltype(GetInputState) * GetInputState;
  decltype(GetQueueStatus) * GetQueueStatus;
  decltype(GetCapture) * GetCapture;
  decltype(SetCapture) * SetCapture;
  decltype(ReleaseCapture) * ReleaseCapture;
  decltype(MsgWaitForMultipleObjects) * MsgWaitForMultipleObjects;
  decltype(MsgWaitForMultipleObjectsEx) * MsgWaitForMultipleObjectsEx;
  decltype(SetTimer) * SetTimer;
  decltype(KillTimer) * KillTimer;
  decltype(IsWindowUnicode) * IsWindowUnicode;
  decltype(EnableWindow) * EnableWindow;
  decltype(IsWindowEnabled) * IsWindowEnabled;
  decltype(LoadAcceleratorsA) * LoadAcceleratorsA;
  decltype(LoadAcceleratorsW) * LoadAcceleratorsW;
  decltype(CreateAcceleratorTableA) * CreateAcceleratorTableA;
  decltype(CreateAcceleratorTableW) * CreateAcceleratorTableW;
  decltype(DestroyAcceleratorTable) * DestroyAcceleratorTable;
  decltype(CopyAcceleratorTableA) * CopyAcceleratorTableA;
  decltype(CopyAcceleratorTableW) * CopyAcceleratorTableW;
  decltype(TranslateAcceleratorA) * TranslateAcceleratorA;
  decltype(TranslateAcceleratorW) * TranslateAcceleratorW;
  decltype(SetCoalescableTimer) * SetCoalescableTimer;
  decltype(GetSystemMetrics) * GetSystemMetrics;
  decltype(LoadMenuA) * LoadMenuA;
  decltype(LoadMenuW) * LoadMenuW;
  decltype(LoadMenuIndirectA) * LoadMenuIndirectA;
  decltype(LoadMenuIndirectW) * LoadMenuIndirectW;
  decltype(GetMenu) * GetMenu;
  decltype(SetMenu) * SetMenu;
  decltype(ChangeMenuA) * ChangeMenuA;
  decltype(ChangeMenuW) * ChangeMenuW;
  decltype(HiliteMenuItem) * HiliteMenuItem;
  decltype(GetMenuStringA) * GetMenuStringA;
  decltype(GetMenuStringW) * GetMenuStringW;
  decltype(GetMenuState) * GetMenuState;
  decltype(DrawMenuBar) * DrawMenuBar;
  decltype(GetSystemMenu) * GetSystemMenu;
  decltype(CreateMenu) * CreateMenu;
  decltype(CreatePopupMenu) * CreatePopupMenu;
  decltype(DestroyMenu) * DestroyMenu;
  decltype(CheckMenuItem) * CheckMenuItem;
  decltype(EnableMenuItem) * EnableMenuItem;
  decltype(GetSubMenu) * GetSubMenu;
  decltype(GetMenuItemID) * GetMenuItemID;
  decltype(GetMenuItemCount) * GetMenuItemCount;
  decltype(InsertMenuA) * InsertMenuA;
  decltype(InsertMenuW) * InsertMenuW;
  decltype(AppendMenuA) * AppendMenuA;
  decltype(AppendMenuW) * AppendMenuW;
  decltype(ModifyMenuA) * ModifyMenuA;
  decltype(ModifyMenuW) * ModifyMenuW;
  decltype(RemoveMenu) * RemoveMenu;
  decltype(DeleteMenu) * DeleteMenu;
  decltype(SetMenuItemBitmaps) * SetMenuItemBitmaps;
  decltype(GetMenuCheckMarkDimensions) * GetMenuCheckMarkDimensions;
  decltype(TrackPopupMenu) * TrackPopupMenu;
  decltype(TrackPopupMenuEx) * TrackPopupMenuEx;
  decltype(GetMenuInfo) * GetMenuInfo;
  decltype(SetMenuInfo) * SetMenuInfo;
  decltype(EndMenu) * EndMenu;
  decltype(CalculatePopupWindowPosition) * CalculatePopupWindowPosition;
  decltype(InsertMenuItemA) * InsertMenuItemA;
  decltype(InsertMenuItemW) * InsertMenuItemW;
  decltype(GetMenuItemInfoA) * GetMenuItemInfoA;
  decltype(GetMenuItemInfoW) * GetMenuItemInfoW;
  decltype(SetMenuItemInfoA) * SetMenuItemInfoA;
  decltype(SetMenuItemInfoW) * SetMenuItemInfoW;
  decltype(GetMenuDefaultItem) * GetMenuDefaultItem;
  decltype(SetMenuDefaultItem) * SetMenuDefaultItem;
  decltype(GetMenuItemRect) * GetMenuItemRect;
  decltype(MenuItemFromPoint) * MenuItemFromPoint;
  decltype(DragObject) * DragObject;
  decltype(DragDetect) * DragDetect;
  decltype(DrawIcon) * DrawIcon;
  decltype(DrawTextA) * DrawTextA;
  decltype(DrawTextW) * DrawTextW;
  decltype(DrawTextExA) * DrawTextExA;
  decltype(DrawTextExW) * DrawTextExW;
  decltype(GrayStringA) * GrayStringA;
  decltype(GrayStringW) * GrayStringW;
  decltype(DrawStateA) * DrawStateA;
  decltype(DrawStateW) * DrawStateW;
  decltype(TabbedTextOutA) * TabbedTextOutA;
  decltype(TabbedTextOutW) * TabbedTextOutW;
  decltype(GetTabbedTextExtentA) * GetTabbedTextExtentA;
  decltype(GetTabbedTextExtentW) * GetTabbedTextExtentW;
  decltype(UpdateWindow) * UpdateWindow;
  decltype(SetActiveWindow) * SetActiveWindow;
  decltype(GetForegroundWindow) * GetForegroundWindow;
  decltype(PaintDesktop) * PaintDesktop;
  decltype(SwitchToThisWindow) * SwitchToThisWindow;
  decltype(SetForegroundWindow) * SetForegroundWindow;
  decltype(AllowSetForegroundWindow) * AllowSetForegroundWindow;
  decltype(LockSetForegroundWindow) * LockSetForegroundWindow;
  decltype(WindowFromDC) * WindowFromDC;
  decltype(GetDC) * GetDC;
  decltype(GetDCEx) * GetDCEx;
  decltype(GetWindowDC) * GetWindowDC;
  decltype(ReleaseDC) * ReleaseDC;
  decltype(BeginPaint) * BeginPaint;
  decltype(EndPaint) * EndPaint;
  decltype(GetUpdateRect) * GetUpdateRect;
  decltype(GetUpdateRgn) * GetUpdateRgn;
  decltype(SetWindowRgn) * SetWindowRgn;
  decltype(GetWindowRgn) * GetWindowRgn;
  decltype(GetWindowRgnBox) * GetWindowRgnBox;
  decltype(ExcludeUpdateRgn) * ExcludeUpdateRgn;
  decltype(InvalidateRect) * InvalidateRect;
  decltype(ValidateRect) * ValidateRect;
  decltype(InvalidateRgn) * InvalidateRgn;
  decltype(ValidateRgn) * ValidateRgn;
  decltype(RedrawWindow) * RedrawWindow;
  decltype(LockWindowUpdate) * LockWindowUpdate;
  decltype(ScrollWindow) * ScrollWindow;
  decltype(ScrollDC) * ScrollDC;
  decltype(ScrollWindowEx) * ScrollWindowEx;
  decltype(SetScrollPos) * SetScrollPos;
  decltype(GetScrollPos) * GetScrollPos;
  decltype(SetScrollRange) * SetScrollRange;
  decltype(GetScrollRange) * GetScrollRange;
  decltype(ShowScrollBar) * ShowScrollBar;
  decltype(EnableScrollBar) * EnableScrollBar;
  decltype(SetPropA) * SetPropA;
  decltype(SetPropW) * SetPropW;
  decltype(GetPropA) * GetPropA;
  decltype(GetPropW) * GetPropW;
  decltype(RemovePropA) * RemovePropA;
  decltype(RemovePropW) * RemovePropW;
  decltype(EnumPropsExA) * EnumPropsExA;
  decltype(EnumPropsExW) * EnumPropsExW;
  decltype(EnumPropsA) * EnumPropsA;
  decltype(EnumPropsW) * EnumPropsW;
  decltype(SetWindowTextA) * SetWindowTextA;
  decltype(SetWindowTextW) * SetWindowTextW;
  decltype(GetWindowTextA) * GetWindowTextA;
  decltype(GetWindowTextW) * GetWindowTextW;
  decltype(GetWindowTextLengthA) * GetWindowTextLengthA;
  decltype(GetWindowTextLengthW) * GetWindowTextLengthW;
  decltype(GetClientRect) * GetClientRect;
  decltype(GetWindowRect) * GetWindowRect;
  decltype(AdjustWindowRect) * AdjustWindowRect;
  decltype(AdjustWindowRectEx) * AdjustWindowRectEx;
  decltype(SetWindowContextHelpId) * SetWindowContextHelpId;
  decltype(GetWindowContextHelpId) * GetWindowContextHelpId;
  decltype(SetMenuContextHelpId) * SetMenuContextHelpId;
  decltype(GetMenuContextHelpId) * GetMenuContextHelpId;
  decltype(MessageBoxA) * MessageBoxA;
  decltype(MessageBoxW) * MessageBoxW;
  decltype(MessageBoxExA) * MessageBoxExA;
  decltype(MessageBoxExW) * MessageBoxExW;
  decltype(MessageBoxIndirectA) * MessageBoxIndirectA;
  decltype(MessageBoxIndirectW) * MessageBoxIndirectW;
  decltype(MessageBeep) * MessageBeep;
  decltype(ShowCursor) * ShowCursor;
  decltype(SetCursorPos) * SetCursorPos;
  decltype(SetCursor) * SetCursor;
  decltype(GetCursorPos) * GetCursorPos;
  decltype(ClipCursor) * ClipCursor;
  decltype(GetClipCursor) * GetClipCursor;
  decltype(GetCursor) * GetCursor;
  decltype(CreateCaret) * CreateCaret;
  decltype(GetCaretBlinkTime) * GetCaretBlinkTime;
  decltype(SetCaretBlinkTime) * SetCaretBlinkTime;
  decltype(DestroyCaret) * DestroyCaret;
  decltype(HideCaret) * HideCaret;
  decltype(ShowCaret) * ShowCaret;
  decltype(SetCaretPos) * SetCaretPos;
  decltype(GetCaretPos) * GetCaretPos;
  decltype(ClientToScreen) * ClientToScreen;
  decltype(ScreenToClient) * ScreenToClient;
  decltype(MapWindowPoints) * MapWindowPoints;
  decltype(WindowFromPoint) * WindowFromPoint;
  decltype(ChildWindowFromPoint) * ChildWindowFromPoint;
  decltype(ChildWindowFromPointEx) * ChildWindowFromPointEx;
  decltype(SetPhysicalCursorPos) * SetPhysicalCursorPos;
  decltype(GetPhysicalCursorPos) * GetPhysicalCursorPos;
  decltype(LogicalToPhysicalPoint) * LogicalToPhysicalPoint;
  decltype(PhysicalToLogicalPoint) * PhysicalToLogicalPoint;
  decltype(WindowFromPhysicalPoint) * WindowFromPhysicalPoint;
  decltype(GetSysColor) * GetSysColor;
  decltype(GetSysColorBrush) * GetSysColorBrush;
  decltype(SetSysColors) * SetSysColors;
  decltype(DrawFocusRect) * DrawFocusRect;
  decltype(FillRect) * FillRect;
  decltype(FrameRect) * FrameRect;
  decltype(InvertRect) * InvertRect;
  decltype(SetRect) * SetRect;
  decltype(SetRectEmpty) * SetRectEmpty;
  decltype(CopyRect) * CopyRect;
  decltype(InflateRect) * InflateRect;
  decltype(IntersectRect) * IntersectRect;
  decltype(UnionRect) * UnionRect;
  decltype(SubtractRect) * SubtractRect;
  decltype(OffsetRect) * OffsetRect;
  decltype(IsRectEmpty) * IsRectEmpty;
  decltype(EqualRect) * EqualRect;
  decltype(PtInRect) * PtInRect;
  decltype(GetWindowWord) * GetWindowWord;
  decltype(SetWindowWord) * SetWindowWord;
  decltype(GetWindowLongA) * GetWindowLongA;
  decltype(GetWindowLongW) * GetWindowLongW;
  decltype(SetWindowLongA) * SetWindowLongA;
  decltype(SetWindowLongW) * SetWindowLongW;
#ifdef _WIN64
  decltype(GetWindowLongPtrA) * GetWindowLongPtrA;
  decltype(GetWindowLongPtrW) * GetWindowLongPtrW;
  decltype(SetWindowLongPtrA) * SetWindowLongPtrA;
  decltype(SetWindowLongPtrW) * SetWindowLongPtrW;
#endif
  decltype(GetClassWord) * GetClassWord;
  decltype(SetClassWord) * SetClassWord;
  decltype(GetClassLongA) * GetClassLongA;
  decltype(GetClassLongW) * GetClassLongW;
  decltype(SetClassLongA) * SetClassLongA;
  decltype(SetClassLongW) * SetClassLongW;
#ifdef _WIN64
  decltype(GetClassLongPtrA) * GetClassLongPtrA;
  decltype(GetClassLongPtrW) * GetClassLongPtrW;
  decltype(SetClassLongPtrA) * SetClassLongPtrA;
  decltype(SetClassLongPtrW) * SetClassLongPtrW;
#endif
  decltype(GetProcessDefaultLayout) * GetProcessDefaultLayout;
  decltype(SetProcessDefaultLayout) * SetProcessDefaultLayout;
  decltype(GetDesktopWindow) * GetDesktopWindow;
  decltype(GetParent) * GetParent;
  decltype(SetParent) * SetParent;
  decltype(EnumChildWindows) * EnumChildWindows;
  decltype(FindWindowA) * FindWindowA;
  decltype(FindWindowW) * FindWindowW;
  decltype(FindWindowExA) * FindWindowExA;
  decltype(FindWindowExW) * FindWindowExW;
  decltype(GetShellWindow) * GetShellWindow;
  decltype(RegisterShellHookWindow) * RegisterShellHookWindow;
  decltype(DeregisterShellHookWindow) * DeregisterShellHookWindow;
  decltype(EnumWindows) * EnumWindows;
  decltype(EnumThreadWindows) * EnumThreadWindows;
  decltype(GetClassNameA) * GetClassNameA;
  decltype(GetClassNameW) * GetClassNameW;
  decltype(GetTopWindow) * GetTopWindow;
  decltype(GetWindowThreadProcessId) * GetWindowThreadProcessId;
  decltype(IsGUIThread) * IsGUIThread;
  decltype(GetLastActivePopup) * GetLastActivePopup;
  decltype(GetWindow) * GetWindow;
  decltype(SetWindowsHookA) * SetWindowsHookA;
  decltype(SetWindowsHookW) * SetWindowsHookW;
  decltype(UnhookWindowsHook) * UnhookWindowsHook;
  decltype(SetWindowsHookExA) * SetWindowsHookExA;
  decltype(SetWindowsHookExW) * SetWindowsHookExW;
  decltype(UnhookWindowsHookEx) * UnhookWindowsHookEx;
  decltype(CallNextHookEx) * CallNextHookEx;
  decltype(CheckMenuRadioItem) * CheckMenuRadioItem;
  decltype(LoadBitmapA) * LoadBitmapA;
  decltype(LoadBitmapW) * LoadBitmapW;
  decltype(LoadCursorA) * LoadCursorA;
  decltype(LoadCursorW) * LoadCursorW;
  decltype(LoadCursorFromFileA) * LoadCursorFromFileA;
  decltype(LoadCursorFromFileW) * LoadCursorFromFileW;
  decltype(CreateCursor) * CreateCursor;
  decltype(DestroyCursor) * DestroyCursor;
  decltype(SetSystemCursor) * SetSystemCursor;
  decltype(LoadIconA) * LoadIconA;
  decltype(LoadIconW) * LoadIconW;
  decltype(PrivateExtractIconsA) * PrivateExtractIconsA;
  decltype(PrivateExtractIconsW) * PrivateExtractIconsW;
  decltype(CreateIcon) * CreateIcon;
  decltype(DestroyIcon) * DestroyIcon;
  decltype(LookupIconIdFromDirectory) * LookupIconIdFromDirectory;
  decltype(LookupIconIdFromDirectoryEx) * LookupIconIdFromDirectoryEx;
  decltype(CreateIconFromResource) * CreateIconFromResource;
  decltype(CreateIconFromResourceEx) * CreateIconFromResourceEx;
  decltype(LoadImageA) * LoadImageA;
  decltype(LoadImageW) * LoadImageW;
  decltype(CopyImage) * CopyImage;
  decltype(DrawIconEx) * DrawIconEx;
  decltype(CreateIconIndirect) * CreateIconIndirect;
  decltype(CopyIcon) * CopyIcon;
  decltype(GetIconInfo) * GetIconInfo;
  decltype(GetIconInfoExA) * GetIconInfoExA;
  decltype(GetIconInfoExW) * GetIconInfoExW;
  decltype(LoadStringA) * LoadStringA;
  decltype(LoadStringW) * LoadStringW;
  decltype(IsDialogMessageA) * IsDialogMessageA;
  decltype(IsDialogMessageW) * IsDialogMessageW;
  decltype(MapDialogRect) * MapDialogRect;
  decltype(DlgDirListA) * DlgDirListA;
  decltype(DlgDirListW) * DlgDirListW;
  decltype(DlgDirSelectExA) * DlgDirSelectExA;
  decltype(DlgDirSelectExW) * DlgDirSelectExW;
  decltype(DlgDirListComboBoxA) * DlgDirListComboBoxA;
  decltype(DlgDirListComboBoxW) * DlgDirListComboBoxW;
  decltype(DlgDirSelectComboBoxExA) * DlgDirSelectComboBoxExA;
  decltype(DlgDirSelectComboBoxExW) * DlgDirSelectComboBoxExW;
  decltype(SetScrollInfo) * SetScrollInfo;
  decltype(GetScrollInfo) * GetScrollInfo;
  decltype(DefFrameProcA) * DefFrameProcA;
  decltype(DefFrameProcW) * DefFrameProcW;
  decltype(DefMDIChildProcA) * DefMDIChildProcA;
  decltype(DefMDIChildProcW) * DefMDIChildProcW;
  decltype(TranslateMDISysAccel) * TranslateMDISysAccel;
  decltype(ArrangeIconicWindows) * ArrangeIconicWindows;
  decltype(CreateMDIWindowA) * CreateMDIWindowA;
  decltype(CreateMDIWindowW) * CreateMDIWindowW;
  decltype(TileWindows) * TileWindows;
  decltype(CascadeWindows) * CascadeWindows;
  decltype(WinHelpA) * WinHelpA;
  decltype(WinHelpW) * WinHelpW;
  decltype(GetGuiResources) * GetGuiResources;
  decltype(ChangeDisplaySettingsA) * ChangeDisplaySettingsA;
  decltype(ChangeDisplaySettingsW) * ChangeDisplaySettingsW;
  decltype(ChangeDisplaySettingsExA) * ChangeDisplaySettingsExA;
  decltype(ChangeDisplaySettingsExW) * ChangeDisplaySettingsExW;
  decltype(EnumDisplaySettingsA) * EnumDisplaySettingsA;
  decltype(EnumDisplaySettingsW) * EnumDisplaySettingsW;
  decltype(EnumDisplaySettingsExA) * EnumDisplaySettingsExA;
  decltype(EnumDisplaySettingsExW) * EnumDisplaySettingsExW;
  decltype(EnumDisplayDevicesA) * EnumDisplayDevicesA;
  decltype(EnumDisplayDevicesW) * EnumDisplayDevicesW;
  decltype(GetDisplayConfigBufferSizes) * GetDisplayConfigBufferSizes;
  decltype(SetDisplayConfig) * SetDisplayConfig;
  decltype(QueryDisplayConfig) * QueryDisplayConfig;
  decltype(DisplayConfigGetDeviceInfo) * DisplayConfigGetDeviceInfo;
  decltype(DisplayConfigSetDeviceInfo) * DisplayConfigSetDeviceInfo;
  decltype(SystemParametersInfoA) * SystemParametersInfoA;
  decltype(SystemParametersInfoW) * SystemParametersInfoW;
  decltype(SetDebugErrorLevel) * SetDebugErrorLevel;
  decltype(SetLastErrorEx) * SetLastErrorEx;
  decltype(InternalGetWindowText) * InternalGetWindowText;
  decltype(CancelShutdown) * CancelShutdown;
  decltype(MonitorFromPoint) * MonitorFromPoint;
  decltype(MonitorFromRect) * MonitorFromRect;
  decltype(MonitorFromWindow) * MonitorFromWindow;
#ifdef WINNT
  decltype(EndTask) * EndTask;
#endif
  decltype(SoundSentry) * SoundSentry;
  decltype(GetMonitorInfoA) * GetMonitorInfoA;
  decltype(GetMonitorInfoW) * GetMonitorInfoW;
  decltype(EnumDisplayMonitors) * EnumDisplayMonitors;
  decltype(NotifyWinEvent) * NotifyWinEvent;
  decltype(SetWinEventHook) * SetWinEventHook;
  decltype(IsWinEventHookInstalled) * IsWinEventHookInstalled;
  decltype(UnhookWinEvent) * UnhookWinEvent;
  decltype(GetGUIThreadInfo) * GetGUIThreadInfo;
  decltype(BlockInput) * BlockInput;
  decltype(GetWindowModuleFileNameA) * GetWindowModuleFileNameA;
  decltype(GetWindowModuleFileNameW) * GetWindowModuleFileNameW;
  decltype(SetProcessDPIAware) * SetProcessDPIAware;
  decltype(IsProcessDPIAware) * IsProcessDPIAware;
  decltype(GetCursorInfo) * GetCursorInfo;
  decltype(GetWindowInfo) * GetWindowInfo;
  decltype(GetTitleBarInfo) * GetTitleBarInfo;
  decltype(GetMenuBarInfo) * GetMenuBarInfo;
  decltype(GetScrollBarInfo) * GetScrollBarInfo;
  decltype(GetComboBoxInfo) * GetComboBoxInfo;
  decltype(GetAncestor) * GetAncestor;
  decltype(RealChildWindowFromPoint) * RealChildWindowFromPoint;
  decltype(RealGetWindowClassA) * RealGetWindowClassA;
  decltype(RealGetWindowClassW) * RealGetWindowClassW;
  decltype(GetAltTabInfoA) * GetAltTabInfoA;
  decltype(GetAltTabInfoW) * GetAltTabInfoW;
  decltype(GetListBoxInfo) * GetListBoxInfo;
  decltype(LockWorkStation) * LockWorkStation;
  decltype(UserHandleGrantAccess) * UserHandleGrantAccess;
  decltype(GetRawInputData) * GetRawInputData;
  decltype(GetRawInputDeviceInfoA) * GetRawInputDeviceInfoA;
  decltype(GetRawInputDeviceInfoW) * GetRawInputDeviceInfoW;
  decltype(GetRawInputBuffer) * GetRawInputBuffer;
  decltype(RegisterRawInputDevices) * RegisterRawInputDevices;
  decltype(GetRegisteredRawInputDevices) * GetRegisteredRawInputDevices;
  decltype(GetRawInputDeviceList) * GetRawInputDeviceList;
  decltype(DefRawInputProc) * DefRawInputProc;
  decltype(GetPointerDevices) * GetPointerDevices;
  decltype(GetPointerDevice) * GetPointerDevice;
  decltype(GetPointerDeviceProperties) * GetPointerDeviceProperties;
  decltype(RegisterPointerDeviceNotifications) * RegisterPointerDeviceNotifications;
  decltype(GetPointerDeviceRects) * GetPointerDeviceRects;
  decltype(GetPointerDeviceCursors) * GetPointerDeviceCursors;
  decltype(GetRawPointerDeviceData) * GetRawPointerDeviceData;
  decltype(ChangeWindowMessageFilter) * ChangeWindowMessageFilter;
  decltype(ChangeWindowMessageFilterEx) * ChangeWindowMessageFilterEx;
  decltype(GetGestureInfo) * GetGestureInfo;
  decltype(GetGestureExtraArgs) * GetGestureExtraArgs;
  decltype(CloseGestureInfoHandle) * CloseGestureInfoHandle;
  decltype(SetGestureConfig) * SetGestureConfig;
  decltype(GetGestureConfig) * GetGestureConfig;
  decltype(ShutdownBlockReasonCreate) * ShutdownBlockReasonCreate;
  decltype(ShutdownBlockReasonQuery) * ShutdownBlockReasonQuery;
  decltype(ShutdownBlockReasonDestroy) * ShutdownBlockReasonDestroy;
  decltype(GetCurrentInputMessageSource) * GetCurrentInputMessageSource;
  decltype(GetCIMSSM) * GetCIMSSM;
  decltype(GetAutoRotationState) * GetAutoRotationState;
  decltype(GetDisplayAutoRotationPreferences) * GetDisplayAutoRotationPreferences;
  decltype(GetDisplayAutoRotationPreferencesByProcessId) * GetDisplayAutoRotationPreferencesByProcessId;
  decltype(SetDisplayAutoRotationPreferences) * SetDisplayAutoRotationPreferences;
  decltype(IsImmersiveProcess) * IsImmersiveProcess;
  decltype(SetProcessRestrictionExemption) * SetProcessRestrictionExemption;
  decltype(GetPointerInputTransform) * GetPointerInputTransform;
  decltype(IsMousePointerEnabled) * IsMousePointerEnabled;

  void init(HMODULE hModule);
}; //User32


void User32::init(HMODULE hModule)
{
  this->wvsprintfA = reinterpret_cast<decltype(::wvsprintfA) *>(GetProcAddress(hModule,"wvsprintfA"));
  this->wvsprintfW = reinterpret_cast<decltype(::wvsprintfW) *>(GetProcAddress(hModule,"wvsprintfW"));
  this->wsprintfA = reinterpret_cast<decltype(::wsprintfA) *>(GetProcAddress(hModule,"wsprintfA"));
  this->wsprintfW = reinterpret_cast<decltype(::wsprintfW) *>(GetProcAddress(hModule,"wsprintfW"));
  this->LoadKeyboardLayoutA = reinterpret_cast<decltype(::LoadKeyboardLayoutA) *>(GetProcAddress(hModule,"LoadKeyboardLayoutA"));
  this->LoadKeyboardLayoutW = reinterpret_cast<decltype(::LoadKeyboardLayoutW) *>(GetProcAddress(hModule,"LoadKeyboardLayoutW"));
  this->ActivateKeyboardLayout = reinterpret_cast<decltype(::ActivateKeyboardLayout) *>(GetProcAddress(hModule,"ActivateKeyboardLayout"));
  this->ToUnicodeEx = reinterpret_cast<decltype(::ToUnicodeEx) *>(GetProcAddress(hModule,"ToUnicodeEx"));
  this->UnloadKeyboardLayout = reinterpret_cast<decltype(::UnloadKeyboardLayout) *>(GetProcAddress(hModule,"UnloadKeyboardLayout"));
  this->GetKeyboardLayoutNameA = reinterpret_cast<decltype(::GetKeyboardLayoutNameA) *>(GetProcAddress(hModule,"GetKeyboardLayoutNameA"));
  this->GetKeyboardLayoutNameW = reinterpret_cast<decltype(::GetKeyboardLayoutNameW) *>(GetProcAddress(hModule,"GetKeyboardLayoutNameW"));
  this->GetKeyboardLayoutList = reinterpret_cast<decltype(::GetKeyboardLayoutList) *>(GetProcAddress(hModule,"GetKeyboardLayoutList"));
  this->GetKeyboardLayout = reinterpret_cast<decltype(::GetKeyboardLayout) *>(GetProcAddress(hModule,"GetKeyboardLayout"));
  this->GetMouseMovePointsEx = reinterpret_cast<decltype(::GetMouseMovePointsEx) *>(GetProcAddress(hModule,"GetMouseMovePointsEx"));
  this->CreateDesktopA = reinterpret_cast<decltype(::CreateDesktopA) *>(GetProcAddress(hModule,"CreateDesktopA"));
  this->CreateDesktopW = reinterpret_cast<decltype(::CreateDesktopW) *>(GetProcAddress(hModule,"CreateDesktopW"));
  this->CreateDesktopExA = reinterpret_cast<decltype(::CreateDesktopExA) *>(GetProcAddress(hModule,"CreateDesktopExA"));
  this->CreateDesktopExW = reinterpret_cast<decltype(::CreateDesktopExW) *>(GetProcAddress(hModule,"CreateDesktopExW"));
  this->OpenDesktopA = reinterpret_cast<decltype(::OpenDesktopA) *>(GetProcAddress(hModule,"OpenDesktopA"));
  this->OpenDesktopW = reinterpret_cast<decltype(::OpenDesktopW) *>(GetProcAddress(hModule,"OpenDesktopW"));
  this->OpenInputDesktop = reinterpret_cast<decltype(::OpenInputDesktop) *>(GetProcAddress(hModule,"OpenInputDesktop"));
  this->EnumDesktopsA = reinterpret_cast<decltype(::EnumDesktopsA) *>(GetProcAddress(hModule,"EnumDesktopsA"));
  this->EnumDesktopsW = reinterpret_cast<decltype(::EnumDesktopsW) *>(GetProcAddress(hModule,"EnumDesktopsW"));
  this->EnumDesktopWindows = reinterpret_cast<decltype(::EnumDesktopWindows) *>(GetProcAddress(hModule,"EnumDesktopWindows"));
  this->SwitchDesktop = reinterpret_cast<decltype(::SwitchDesktop) *>(GetProcAddress(hModule,"SwitchDesktop"));
  this->SetThreadDesktop = reinterpret_cast<decltype(::SetThreadDesktop) *>(GetProcAddress(hModule,"SetThreadDesktop"));
  this->CloseDesktop = reinterpret_cast<decltype(::CloseDesktop) *>(GetProcAddress(hModule,"CloseDesktop"));
  this->GetThreadDesktop = reinterpret_cast<decltype(::GetThreadDesktop) *>(GetProcAddress(hModule,"GetThreadDesktop"));
  this->CreateWindowStationA = reinterpret_cast<decltype(::CreateWindowStationA) *>(GetProcAddress(hModule,"CreateWindowStationA"));
  this->CreateWindowStationW = reinterpret_cast<decltype(::CreateWindowStationW) *>(GetProcAddress(hModule,"CreateWindowStationW"));
  this->OpenWindowStationA = reinterpret_cast<decltype(::OpenWindowStationA) *>(GetProcAddress(hModule,"OpenWindowStationA"));
  this->OpenWindowStationW = reinterpret_cast<decltype(::OpenWindowStationW) *>(GetProcAddress(hModule,"OpenWindowStationW"));
  this->EnumWindowStationsA = reinterpret_cast<decltype(::EnumWindowStationsA) *>(GetProcAddress(hModule,"EnumWindowStationsA"));
  this->EnumWindowStationsW = reinterpret_cast<decltype(::EnumWindowStationsW) *>(GetProcAddress(hModule,"EnumWindowStationsW"));
  this->CloseWindowStation = reinterpret_cast<decltype(::CloseWindowStation) *>(GetProcAddress(hModule,"CloseWindowStation"));
  this->SetProcessWindowStation = reinterpret_cast<decltype(::SetProcessWindowStation) *>(GetProcAddress(hModule,"SetProcessWindowStation"));
  this->GetProcessWindowStation = reinterpret_cast<decltype(::GetProcessWindowStation) *>(GetProcAddress(hModule,"GetProcessWindowStation"));
  this->SetUserObjectSecurity = reinterpret_cast<decltype(::SetUserObjectSecurity) *>(GetProcAddress(hModule,"SetUserObjectSecurity"));
  this->GetUserObjectSecurity = reinterpret_cast<decltype(::GetUserObjectSecurity) *>(GetProcAddress(hModule,"GetUserObjectSecurity"));
  this->GetUserObjectInformationA = reinterpret_cast<decltype(::GetUserObjectInformationA) *>(GetProcAddress(hModule,"GetUserObjectInformationA"));
  this->GetUserObjectInformationW = reinterpret_cast<decltype(::GetUserObjectInformationW) *>(GetProcAddress(hModule,"GetUserObjectInformationW"));
  this->SetUserObjectInformationA = reinterpret_cast<decltype(::SetUserObjectInformationA) *>(GetProcAddress(hModule,"SetUserObjectInformationA"));
  this->SetUserObjectInformationW = reinterpret_cast<decltype(::SetUserObjectInformationW) *>(GetProcAddress(hModule,"SetUserObjectInformationW"));
  this->IsHungAppWindow = reinterpret_cast<decltype(::IsHungAppWindow) *>(GetProcAddress(hModule,"IsHungAppWindow"));
  this->DisableProcessWindowsGhosting = reinterpret_cast<decltype(::DisableProcessWindowsGhosting) *>(GetProcAddress(hModule,"DisableProcessWindowsGhosting"));
  this->RegisterWindowMessageA = reinterpret_cast<decltype(::RegisterWindowMessageA) *>(GetProcAddress(hModule,"RegisterWindowMessageA"));
  this->RegisterWindowMessageW = reinterpret_cast<decltype(::RegisterWindowMessageW) *>(GetProcAddress(hModule,"RegisterWindowMessageW"));
  this->TrackMouseEvent = reinterpret_cast<decltype(::TrackMouseEvent) *>(GetProcAddress(hModule,"TrackMouseEvent"));
  this->DrawEdge = reinterpret_cast<decltype(::DrawEdge) *>(GetProcAddress(hModule,"DrawEdge"));
  this->DrawFrameControl = reinterpret_cast<decltype(::DrawFrameControl) *>(GetProcAddress(hModule,"DrawFrameControl"));
  this->DrawCaption = reinterpret_cast<decltype(::DrawCaption) *>(GetProcAddress(hModule,"DrawCaption"));
  this->DrawAnimatedRects = reinterpret_cast<decltype(::DrawAnimatedRects) *>(GetProcAddress(hModule,"DrawAnimatedRects"));
  this->GetMessageA = reinterpret_cast<decltype(::GetMessageA) *>(GetProcAddress(hModule,"GetMessageA"));
  this->GetMessageW = reinterpret_cast<decltype(::GetMessageW) *>(GetProcAddress(hModule,"GetMessageW"));
  this->TranslateMessage = reinterpret_cast<decltype(::TranslateMessage) *>(GetProcAddress(hModule,"TranslateMessage"));
  this->DispatchMessageA = reinterpret_cast<decltype(::DispatchMessageA) *>(GetProcAddress(hModule,"DispatchMessageA"));
  this->DispatchMessageW = reinterpret_cast<decltype(::DispatchMessageW) *>(GetProcAddress(hModule,"DispatchMessageW"));
  this->SetMessageQueue = reinterpret_cast<decltype(::SetMessageQueue) *>(GetProcAddress(hModule,"SetMessageQueue"));
  this->PeekMessageA = reinterpret_cast<decltype(::PeekMessageA) *>(GetProcAddress(hModule,"PeekMessageA"));
  this->PeekMessageW = reinterpret_cast<decltype(::PeekMessageW) *>(GetProcAddress(hModule,"PeekMessageW"));
  this->RegisterHotKey = reinterpret_cast<decltype(::RegisterHotKey) *>(GetProcAddress(hModule,"RegisterHotKey"));
  this->UnregisterHotKey = reinterpret_cast<decltype(::UnregisterHotKey) *>(GetProcAddress(hModule,"UnregisterHotKey"));
  this->ExitWindowsEx = reinterpret_cast<decltype(::ExitWindowsEx) *>(GetProcAddress(hModule,"ExitWindowsEx"));
  this->SwapMouseButton = reinterpret_cast<decltype(::SwapMouseButton) *>(GetProcAddress(hModule,"SwapMouseButton"));
  this->GetMessagePos = reinterpret_cast<decltype(::GetMessagePos) *>(GetProcAddress(hModule,"GetMessagePos"));
  this->GetMessageTime = reinterpret_cast<decltype(::GetMessageTime) *>(GetProcAddress(hModule,"GetMessageTime"));
  this->GetMessageExtraInfo = reinterpret_cast<decltype(::GetMessageExtraInfo) *>(GetProcAddress(hModule,"GetMessageExtraInfo"));
  this->GetUnpredictedMessagePos = reinterpret_cast<decltype(::GetUnpredictedMessagePos) *>(GetProcAddress(hModule,"GetUnpredictedMessagePos"));
  this->IsWow64Message = reinterpret_cast<decltype(::IsWow64Message) *>(GetProcAddress(hModule,"IsWow64Message"));
  this->SetMessageExtraInfo = reinterpret_cast<decltype(::SetMessageExtraInfo) *>(GetProcAddress(hModule,"SetMessageExtraInfo"));
  this->SendMessageA = reinterpret_cast<decltype(::SendMessageA) *>(GetProcAddress(hModule,"SendMessageA"));
  this->SendMessageW = reinterpret_cast<decltype(::SendMessageW) *>(GetProcAddress(hModule,"SendMessageW"));
  this->SendMessageTimeoutA = reinterpret_cast<decltype(::SendMessageTimeoutA) *>(GetProcAddress(hModule,"SendMessageTimeoutA"));
  this->SendMessageTimeoutW = reinterpret_cast<decltype(::SendMessageTimeoutW) *>(GetProcAddress(hModule,"SendMessageTimeoutW"));
  this->SendNotifyMessageA = reinterpret_cast<decltype(::SendNotifyMessageA) *>(GetProcAddress(hModule,"SendNotifyMessageA"));
  this->SendNotifyMessageW = reinterpret_cast<decltype(::SendNotifyMessageW) *>(GetProcAddress(hModule,"SendNotifyMessageW"));
  this->SendMessageCallbackA = reinterpret_cast<decltype(::SendMessageCallbackA) *>(GetProcAddress(hModule,"SendMessageCallbackA"));
  this->SendMessageCallbackW = reinterpret_cast<decltype(::SendMessageCallbackW) *>(GetProcAddress(hModule,"SendMessageCallbackW"));
  this->BroadcastSystemMessageExA = reinterpret_cast<decltype(::BroadcastSystemMessageExA) *>(GetProcAddress(hModule,"BroadcastSystemMessageExA"));
  this->BroadcastSystemMessageExW = reinterpret_cast<decltype(::BroadcastSystemMessageExW) *>(GetProcAddress(hModule,"BroadcastSystemMessageExW"));
  this->BroadcastSystemMessageA = reinterpret_cast<decltype(::BroadcastSystemMessageA) *>(GetProcAddress(hModule,"BroadcastSystemMessageA"));
  this->BroadcastSystemMessageW = reinterpret_cast<decltype(::BroadcastSystemMessageW) *>(GetProcAddress(hModule,"BroadcastSystemMessageW"));
  this->RegisterPowerSettingNotification = reinterpret_cast<decltype(::RegisterPowerSettingNotification) *>(GetProcAddress(hModule,"RegisterPowerSettingNotification"));
  this->UnregisterPowerSettingNotification = reinterpret_cast<decltype(::UnregisterPowerSettingNotification) *>(GetProcAddress(hModule,"UnregisterPowerSettingNotification"));
  this->RegisterSuspendResumeNotification = reinterpret_cast<decltype(::RegisterSuspendResumeNotification) *>(GetProcAddress(hModule,"RegisterSuspendResumeNotification"));
  this->UnregisterSuspendResumeNotification = reinterpret_cast<decltype(::UnregisterSuspendResumeNotification) *>(GetProcAddress(hModule,"UnregisterSuspendResumeNotification"));
  this->PostMessageA = reinterpret_cast<decltype(::PostMessageA) *>(GetProcAddress(hModule,"PostMessageA"));
  this->PostMessageW = reinterpret_cast<decltype(::PostMessageW) *>(GetProcAddress(hModule,"PostMessageW"));
  this->PostThreadMessageA = reinterpret_cast<decltype(::PostThreadMessageA) *>(GetProcAddress(hModule,"PostThreadMessageA"));
  this->PostThreadMessageW = reinterpret_cast<decltype(::PostThreadMessageW) *>(GetProcAddress(hModule,"PostThreadMessageW"));
  this->AttachThreadInput = reinterpret_cast<decltype(::AttachThreadInput) *>(GetProcAddress(hModule,"AttachThreadInput"));
  this->ReplyMessage = reinterpret_cast<decltype(::ReplyMessage) *>(GetProcAddress(hModule,"ReplyMessage"));
  this->WaitMessage = reinterpret_cast<decltype(::WaitMessage) *>(GetProcAddress(hModule,"WaitMessage"));
  this->WaitForInputIdle = reinterpret_cast<decltype(::WaitForInputIdle) *>(GetProcAddress(hModule,"WaitForInputIdle"));
  this->DefWindowProcA = reinterpret_cast<decltype(::DefWindowProcA) *>(GetProcAddress(hModule,"DefWindowProcA"));
  this->DefWindowProcW = reinterpret_cast<decltype(::DefWindowProcW) *>(GetProcAddress(hModule,"DefWindowProcW"));
  this->PostQuitMessage = reinterpret_cast<decltype(::PostQuitMessage) *>(GetProcAddress(hModule,"PostQuitMessage"));
  this->InSendMessage = reinterpret_cast<decltype(::InSendMessage) *>(GetProcAddress(hModule,"InSendMessage"));
  this->InSendMessageEx = reinterpret_cast<decltype(::InSendMessageEx) *>(GetProcAddress(hModule,"InSendMessageEx"));
  this->GetDoubleClickTime = reinterpret_cast<decltype(::GetDoubleClickTime) *>(GetProcAddress(hModule,"GetDoubleClickTime"));
  this->SetDoubleClickTime = reinterpret_cast<decltype(::SetDoubleClickTime) *>(GetProcAddress(hModule,"SetDoubleClickTime"));
  this->RegisterClassA = reinterpret_cast<decltype(::RegisterClassA) *>(GetProcAddress(hModule,"RegisterClassA"));
  this->RegisterClassW = reinterpret_cast<decltype(::RegisterClassW) *>(GetProcAddress(hModule,"RegisterClassW"));
  this->UnregisterClassA = reinterpret_cast<decltype(::UnregisterClassA) *>(GetProcAddress(hModule,"UnregisterClassA"));
  this->UnregisterClassW = reinterpret_cast<decltype(::UnregisterClassW) *>(GetProcAddress(hModule,"UnregisterClassW"));
  this->GetClassInfoA = reinterpret_cast<decltype(::GetClassInfoA) *>(GetProcAddress(hModule,"GetClassInfoA"));
  this->GetClassInfoW = reinterpret_cast<decltype(::GetClassInfoW) *>(GetProcAddress(hModule,"GetClassInfoW"));
  this->RegisterClassExA = reinterpret_cast<decltype(::RegisterClassExA) *>(GetProcAddress(hModule,"RegisterClassExA"));
  this->RegisterClassExW = reinterpret_cast<decltype(::RegisterClassExW) *>(GetProcAddress(hModule,"RegisterClassExW"));
  this->GetClassInfoExA = reinterpret_cast<decltype(::GetClassInfoExA) *>(GetProcAddress(hModule,"GetClassInfoExA"));
  this->GetClassInfoExW = reinterpret_cast<decltype(::GetClassInfoExW) *>(GetProcAddress(hModule,"GetClassInfoExW"));
  this->CallWindowProcA = reinterpret_cast<decltype(::CallWindowProcA) *>(GetProcAddress(hModule,"CallWindowProcA"));
  this->CallWindowProcW = reinterpret_cast<decltype(::CallWindowProcW) *>(GetProcAddress(hModule,"CallWindowProcW"));
  this->RegisterDeviceNotificationA = reinterpret_cast<decltype(::RegisterDeviceNotificationA) *>(GetProcAddress(hModule,"RegisterDeviceNotificationA"));
  this->RegisterDeviceNotificationW = reinterpret_cast<decltype(::RegisterDeviceNotificationW) *>(GetProcAddress(hModule,"RegisterDeviceNotificationW"));
  this->UnregisterDeviceNotification = reinterpret_cast<decltype(::UnregisterDeviceNotification) *>(GetProcAddress(hModule,"UnregisterDeviceNotification"));
  this->CreateWindowExA = reinterpret_cast<decltype(::CreateWindowExA) *>(GetProcAddress(hModule,"CreateWindowExA"));
  this->CreateWindowExW = reinterpret_cast<decltype(::CreateWindowExW) *>(GetProcAddress(hModule,"CreateWindowExW"));
  this->IsWindow = reinterpret_cast<decltype(::IsWindow) *>(GetProcAddress(hModule,"IsWindow"));
  this->IsMenu = reinterpret_cast<decltype(::IsMenu) *>(GetProcAddress(hModule,"IsMenu"));
  this->IsChild = reinterpret_cast<decltype(::IsChild) *>(GetProcAddress(hModule,"IsChild"));
  this->DestroyWindow = reinterpret_cast<decltype(::DestroyWindow) *>(GetProcAddress(hModule,"DestroyWindow"));
  this->ShowWindow = reinterpret_cast<decltype(::ShowWindow) *>(GetProcAddress(hModule,"ShowWindow"));
  this->AnimateWindow = reinterpret_cast<decltype(::AnimateWindow) *>(GetProcAddress(hModule,"AnimateWindow"));
  this->UpdateLayeredWindow = reinterpret_cast<decltype(::UpdateLayeredWindow) *>(GetProcAddress(hModule,"UpdateLayeredWindow"));
  this->UpdateLayeredWindowIndirect = reinterpret_cast<decltype(::UpdateLayeredWindowIndirect) *>(GetProcAddress(hModule,"UpdateLayeredWindowIndirect"));
  this->GetLayeredWindowAttributes = reinterpret_cast<decltype(::GetLayeredWindowAttributes) *>(GetProcAddress(hModule,"GetLayeredWindowAttributes"));
  this->PrintWindow = reinterpret_cast<decltype(::PrintWindow) *>(GetProcAddress(hModule,"PrintWindow"));
  this->SetLayeredWindowAttributes = reinterpret_cast<decltype(::SetLayeredWindowAttributes) *>(GetProcAddress(hModule,"SetLayeredWindowAttributes"));
  this->ShowWindowAsync = reinterpret_cast<decltype(::ShowWindowAsync) *>(GetProcAddress(hModule,"ShowWindowAsync"));
  this->FlashWindow = reinterpret_cast<decltype(::FlashWindow) *>(GetProcAddress(hModule,"FlashWindow"));
  this->FlashWindowEx = reinterpret_cast<decltype(::FlashWindowEx) *>(GetProcAddress(hModule,"FlashWindowEx"));
  this->ShowOwnedPopups = reinterpret_cast<decltype(::ShowOwnedPopups) *>(GetProcAddress(hModule,"ShowOwnedPopups"));
  this->OpenIcon = reinterpret_cast<decltype(::OpenIcon) *>(GetProcAddress(hModule,"OpenIcon"));
  this->CloseWindow = reinterpret_cast<decltype(::CloseWindow) *>(GetProcAddress(hModule,"CloseWindow"));
  this->MoveWindow = reinterpret_cast<decltype(::MoveWindow) *>(GetProcAddress(hModule,"MoveWindow"));
  this->SetWindowPos = reinterpret_cast<decltype(::SetWindowPos) *>(GetProcAddress(hModule,"SetWindowPos"));
  this->GetWindowPlacement = reinterpret_cast<decltype(::GetWindowPlacement) *>(GetProcAddress(hModule,"GetWindowPlacement"));
  this->SetWindowPlacement = reinterpret_cast<decltype(::SetWindowPlacement) *>(GetProcAddress(hModule,"SetWindowPlacement"));
  this->GetWindowDisplayAffinity = reinterpret_cast<decltype(::GetWindowDisplayAffinity) *>(GetProcAddress(hModule,"GetWindowDisplayAffinity"));
  this->SetWindowDisplayAffinity = reinterpret_cast<decltype(::SetWindowDisplayAffinity) *>(GetProcAddress(hModule,"SetWindowDisplayAffinity"));
  this->BeginDeferWindowPos = reinterpret_cast<decltype(::BeginDeferWindowPos) *>(GetProcAddress(hModule,"BeginDeferWindowPos"));
  this->DeferWindowPos = reinterpret_cast<decltype(::DeferWindowPos) *>(GetProcAddress(hModule,"DeferWindowPos"));
  this->EndDeferWindowPos = reinterpret_cast<decltype(::EndDeferWindowPos) *>(GetProcAddress(hModule,"EndDeferWindowPos"));
  this->IsWindowVisible = reinterpret_cast<decltype(::IsWindowVisible) *>(GetProcAddress(hModule,"IsWindowVisible"));
  this->IsIconic = reinterpret_cast<decltype(::IsIconic) *>(GetProcAddress(hModule,"IsIconic"));
  this->AnyPopup = reinterpret_cast<decltype(::AnyPopup) *>(GetProcAddress(hModule,"AnyPopup"));
  this->BringWindowToTop = reinterpret_cast<decltype(::BringWindowToTop) *>(GetProcAddress(hModule,"BringWindowToTop"));
  this->IsZoomed = reinterpret_cast<decltype(::IsZoomed) *>(GetProcAddress(hModule,"IsZoomed"));
  this->CreateDialogParamA = reinterpret_cast<decltype(::CreateDialogParamA) *>(GetProcAddress(hModule,"CreateDialogParamA"));
  this->CreateDialogParamW = reinterpret_cast<decltype(::CreateDialogParamW) *>(GetProcAddress(hModule,"CreateDialogParamW"));
  this->CreateDialogIndirectParamA = reinterpret_cast<decltype(::CreateDialogIndirectParamA) *>(GetProcAddress(hModule,"CreateDialogIndirectParamA"));
  this->CreateDialogIndirectParamW = reinterpret_cast<decltype(::CreateDialogIndirectParamW) *>(GetProcAddress(hModule,"CreateDialogIndirectParamW"));
  this->DialogBoxParamA = reinterpret_cast<decltype(::DialogBoxParamA) *>(GetProcAddress(hModule,"DialogBoxParamA"));
  this->DialogBoxParamW = reinterpret_cast<decltype(::DialogBoxParamW) *>(GetProcAddress(hModule,"DialogBoxParamW"));
  this->DialogBoxIndirectParamA = reinterpret_cast<decltype(::DialogBoxIndirectParamA) *>(GetProcAddress(hModule,"DialogBoxIndirectParamA"));
  this->DialogBoxIndirectParamW = reinterpret_cast<decltype(::DialogBoxIndirectParamW) *>(GetProcAddress(hModule,"DialogBoxIndirectParamW"));
  this->EndDialog = reinterpret_cast<decltype(::EndDialog) *>(GetProcAddress(hModule,"EndDialog"));
  this->GetDlgItem = reinterpret_cast<decltype(::GetDlgItem) *>(GetProcAddress(hModule,"GetDlgItem"));
  this->SetDlgItemInt = reinterpret_cast<decltype(::SetDlgItemInt) *>(GetProcAddress(hModule,"SetDlgItemInt"));
  this->GetDlgItemInt = reinterpret_cast<decltype(::GetDlgItemInt) *>(GetProcAddress(hModule,"GetDlgItemInt"));
  this->SetDlgItemTextA = reinterpret_cast<decltype(::SetDlgItemTextA) *>(GetProcAddress(hModule,"SetDlgItemTextA"));
  this->SetDlgItemTextW = reinterpret_cast<decltype(::SetDlgItemTextW) *>(GetProcAddress(hModule,"SetDlgItemTextW"));
  this->GetDlgItemTextA = reinterpret_cast<decltype(::GetDlgItemTextA) *>(GetProcAddress(hModule,"GetDlgItemTextA"));
  this->GetDlgItemTextW = reinterpret_cast<decltype(::GetDlgItemTextW) *>(GetProcAddress(hModule,"GetDlgItemTextW"));
  this->CheckDlgButton = reinterpret_cast<decltype(::CheckDlgButton) *>(GetProcAddress(hModule,"CheckDlgButton"));
  this->CheckRadioButton = reinterpret_cast<decltype(::CheckRadioButton) *>(GetProcAddress(hModule,"CheckRadioButton"));
  this->IsDlgButtonChecked = reinterpret_cast<decltype(::IsDlgButtonChecked) *>(GetProcAddress(hModule,"IsDlgButtonChecked"));
  this->SendDlgItemMessageA = reinterpret_cast<decltype(::SendDlgItemMessageA) *>(GetProcAddress(hModule,"SendDlgItemMessageA"));
  this->SendDlgItemMessageW = reinterpret_cast<decltype(::SendDlgItemMessageW) *>(GetProcAddress(hModule,"SendDlgItemMessageW"));
  this->GetNextDlgGroupItem = reinterpret_cast<decltype(::GetNextDlgGroupItem) *>(GetProcAddress(hModule,"GetNextDlgGroupItem"));
  this->GetNextDlgTabItem = reinterpret_cast<decltype(::GetNextDlgTabItem) *>(GetProcAddress(hModule,"GetNextDlgTabItem"));
  this->GetDlgCtrlID = reinterpret_cast<decltype(::GetDlgCtrlID) *>(GetProcAddress(hModule,"GetDlgCtrlID"));
  this->GetDialogBaseUnits = reinterpret_cast<decltype(::GetDialogBaseUnits) *>(GetProcAddress(hModule,"GetDialogBaseUnits"));
  this->DefDlgProcA = reinterpret_cast<decltype(::DefDlgProcA) *>(GetProcAddress(hModule,"DefDlgProcA"));
  this->DefDlgProcW = reinterpret_cast<decltype(::DefDlgProcW) *>(GetProcAddress(hModule,"DefDlgProcW"));
  this->CallMsgFilterA = reinterpret_cast<decltype(::CallMsgFilterA) *>(GetProcAddress(hModule,"CallMsgFilterA"));
  this->CallMsgFilterW = reinterpret_cast<decltype(::CallMsgFilterW) *>(GetProcAddress(hModule,"CallMsgFilterW"));
  this->OpenClipboard = reinterpret_cast<decltype(::OpenClipboard) *>(GetProcAddress(hModule,"OpenClipboard"));
  this->CloseClipboard = reinterpret_cast<decltype(::CloseClipboard) *>(GetProcAddress(hModule,"CloseClipboard"));
  this->GetClipboardSequenceNumber = reinterpret_cast<decltype(::GetClipboardSequenceNumber) *>(GetProcAddress(hModule,"GetClipboardSequenceNumber"));
  this->GetClipboardOwner = reinterpret_cast<decltype(::GetClipboardOwner) *>(GetProcAddress(hModule,"GetClipboardOwner"));
  this->SetClipboardViewer = reinterpret_cast<decltype(::SetClipboardViewer) *>(GetProcAddress(hModule,"SetClipboardViewer"));
  this->GetClipboardViewer = reinterpret_cast<decltype(::GetClipboardViewer) *>(GetProcAddress(hModule,"GetClipboardViewer"));
  this->ChangeClipboardChain = reinterpret_cast<decltype(::ChangeClipboardChain) *>(GetProcAddress(hModule,"ChangeClipboardChain"));
  this->SetClipboardData = reinterpret_cast<decltype(::SetClipboardData) *>(GetProcAddress(hModule,"SetClipboardData"));
  this->GetClipboardData = reinterpret_cast<decltype(::GetClipboardData) *>(GetProcAddress(hModule,"GetClipboardData"));
  this->RegisterClipboardFormatA = reinterpret_cast<decltype(::RegisterClipboardFormatA) *>(GetProcAddress(hModule,"RegisterClipboardFormatA"));
  this->RegisterClipboardFormatW = reinterpret_cast<decltype(::RegisterClipboardFormatW) *>(GetProcAddress(hModule,"RegisterClipboardFormatW"));
  this->CountClipboardFormats = reinterpret_cast<decltype(::CountClipboardFormats) *>(GetProcAddress(hModule,"CountClipboardFormats"));
  this->EnumClipboardFormats = reinterpret_cast<decltype(::EnumClipboardFormats) *>(GetProcAddress(hModule,"EnumClipboardFormats"));
  this->GetClipboardFormatNameA = reinterpret_cast<decltype(::GetClipboardFormatNameA) *>(GetProcAddress(hModule,"GetClipboardFormatNameA"));
  this->GetClipboardFormatNameW = reinterpret_cast<decltype(::GetClipboardFormatNameW) *>(GetProcAddress(hModule,"GetClipboardFormatNameW"));
  this->EmptyClipboard = reinterpret_cast<decltype(::EmptyClipboard) *>(GetProcAddress(hModule,"EmptyClipboard"));
  this->IsClipboardFormatAvailable = reinterpret_cast<decltype(::IsClipboardFormatAvailable) *>(GetProcAddress(hModule,"IsClipboardFormatAvailable"));
  this->GetPriorityClipboardFormat = reinterpret_cast<decltype(::GetPriorityClipboardFormat) *>(GetProcAddress(hModule,"GetPriorityClipboardFormat"));
  this->GetOpenClipboardWindow = reinterpret_cast<decltype(::GetOpenClipboardWindow) *>(GetProcAddress(hModule,"GetOpenClipboardWindow"));
  this->AddClipboardFormatListener = reinterpret_cast<decltype(::AddClipboardFormatListener) *>(GetProcAddress(hModule,"AddClipboardFormatListener"));
  this->RemoveClipboardFormatListener = reinterpret_cast<decltype(::RemoveClipboardFormatListener) *>(GetProcAddress(hModule,"RemoveClipboardFormatListener"));
  this->GetUpdatedClipboardFormats = reinterpret_cast<decltype(::GetUpdatedClipboardFormats) *>(GetProcAddress(hModule,"GetUpdatedClipboardFormats"));
  this->CharToOemA = reinterpret_cast<decltype(::CharToOemA) *>(GetProcAddress(hModule,"CharToOemA"));
  this->CharToOemW = reinterpret_cast<decltype(::CharToOemW) *>(GetProcAddress(hModule,"CharToOemW"));
  this->OemToCharA = reinterpret_cast<decltype(::OemToCharA) *>(GetProcAddress(hModule,"OemToCharA"));
  this->OemToCharW = reinterpret_cast<decltype(::OemToCharW) *>(GetProcAddress(hModule,"OemToCharW"));
  this->CharToOemBuffA = reinterpret_cast<decltype(::CharToOemBuffA) *>(GetProcAddress(hModule,"CharToOemBuffA"));
  this->CharToOemBuffW = reinterpret_cast<decltype(::CharToOemBuffW) *>(GetProcAddress(hModule,"CharToOemBuffW"));
  this->OemToCharBuffA = reinterpret_cast<decltype(::OemToCharBuffA) *>(GetProcAddress(hModule,"OemToCharBuffA"));
  this->OemToCharBuffW = reinterpret_cast<decltype(::OemToCharBuffW) *>(GetProcAddress(hModule,"OemToCharBuffW"));
  this->CharUpperA = reinterpret_cast<decltype(::CharUpperA) *>(GetProcAddress(hModule,"CharUpperA"));
  this->CharUpperW = reinterpret_cast<decltype(::CharUpperW) *>(GetProcAddress(hModule,"CharUpperW"));
  this->CharUpperBuffA = reinterpret_cast<decltype(::CharUpperBuffA) *>(GetProcAddress(hModule,"CharUpperBuffA"));
  this->CharUpperBuffW = reinterpret_cast<decltype(::CharUpperBuffW) *>(GetProcAddress(hModule,"CharUpperBuffW"));
  this->CharLowerA = reinterpret_cast<decltype(::CharLowerA) *>(GetProcAddress(hModule,"CharLowerA"));
  this->CharLowerW = reinterpret_cast<decltype(::CharLowerW) *>(GetProcAddress(hModule,"CharLowerW"));
  this->CharLowerBuffA = reinterpret_cast<decltype(::CharLowerBuffA) *>(GetProcAddress(hModule,"CharLowerBuffA"));
  this->CharLowerBuffW = reinterpret_cast<decltype(::CharLowerBuffW) *>(GetProcAddress(hModule,"CharLowerBuffW"));
  this->CharNextA = reinterpret_cast<decltype(::CharNextA) *>(GetProcAddress(hModule,"CharNextA"));
  this->CharNextW = reinterpret_cast<decltype(::CharNextW) *>(GetProcAddress(hModule,"CharNextW"));
  this->CharPrevA = reinterpret_cast<decltype(::CharPrevA) *>(GetProcAddress(hModule,"CharPrevA"));
  this->CharPrevW = reinterpret_cast<decltype(::CharPrevW) *>(GetProcAddress(hModule,"CharPrevW"));
  this->CharNextExA = reinterpret_cast<decltype(::CharNextExA) *>(GetProcAddress(hModule,"CharNextExA"));
  this->CharPrevExA = reinterpret_cast<decltype(::CharPrevExA) *>(GetProcAddress(hModule,"CharPrevExA"));
  this->IsCharAlphaA = reinterpret_cast<decltype(::IsCharAlphaA) *>(GetProcAddress(hModule,"IsCharAlphaA"));
  this->IsCharAlphaW = reinterpret_cast<decltype(::IsCharAlphaW) *>(GetProcAddress(hModule,"IsCharAlphaW"));
  this->IsCharAlphaNumericA = reinterpret_cast<decltype(::IsCharAlphaNumericA) *>(GetProcAddress(hModule,"IsCharAlphaNumericA"));
  this->IsCharAlphaNumericW = reinterpret_cast<decltype(::IsCharAlphaNumericW) *>(GetProcAddress(hModule,"IsCharAlphaNumericW"));
  this->IsCharUpperA = reinterpret_cast<decltype(::IsCharUpperA) *>(GetProcAddress(hModule,"IsCharUpperA"));
  this->IsCharUpperW = reinterpret_cast<decltype(::IsCharUpperW) *>(GetProcAddress(hModule,"IsCharUpperW"));
  this->IsCharLowerA = reinterpret_cast<decltype(::IsCharLowerA) *>(GetProcAddress(hModule,"IsCharLowerA"));
  this->IsCharLowerW = reinterpret_cast<decltype(::IsCharLowerW) *>(GetProcAddress(hModule,"IsCharLowerW"));
  this->SetFocus = reinterpret_cast<decltype(::SetFocus) *>(GetProcAddress(hModule,"SetFocus"));
  this->GetActiveWindow = reinterpret_cast<decltype(::GetActiveWindow) *>(GetProcAddress(hModule,"GetActiveWindow"));
  this->GetFocus = reinterpret_cast<decltype(::GetFocus) *>(GetProcAddress(hModule,"GetFocus"));
  this->GetKBCodePage = reinterpret_cast<decltype(::GetKBCodePage) *>(GetProcAddress(hModule,"GetKBCodePage"));
  this->GetKeyState = reinterpret_cast<decltype(::GetKeyState) *>(GetProcAddress(hModule,"GetKeyState"));
  this->GetAsyncKeyState = reinterpret_cast<decltype(::GetAsyncKeyState) *>(GetProcAddress(hModule,"GetAsyncKeyState"));
  this->GetKeyboardState = reinterpret_cast<decltype(::GetKeyboardState) *>(GetProcAddress(hModule,"GetKeyboardState"));
  this->SetKeyboardState = reinterpret_cast<decltype(::SetKeyboardState) *>(GetProcAddress(hModule,"SetKeyboardState"));
  this->GetKeyNameTextA = reinterpret_cast<decltype(::GetKeyNameTextA) *>(GetProcAddress(hModule,"GetKeyNameTextA"));
  this->GetKeyNameTextW = reinterpret_cast<decltype(::GetKeyNameTextW) *>(GetProcAddress(hModule,"GetKeyNameTextW"));
  this->GetKeyboardType = reinterpret_cast<decltype(::GetKeyboardType) *>(GetProcAddress(hModule,"GetKeyboardType"));
  this->ToAscii = reinterpret_cast<decltype(::ToAscii) *>(GetProcAddress(hModule,"ToAscii"));
  this->ToAsciiEx = reinterpret_cast<decltype(::ToAsciiEx) *>(GetProcAddress(hModule,"ToAsciiEx"));
  this->ToUnicode = reinterpret_cast<decltype(::ToUnicode) *>(GetProcAddress(hModule,"ToUnicode"));
  this->OemKeyScan = reinterpret_cast<decltype(::OemKeyScan) *>(GetProcAddress(hModule,"OemKeyScan"));
  this->VkKeyScanA = reinterpret_cast<decltype(::VkKeyScanA) *>(GetProcAddress(hModule,"VkKeyScanA"));
  this->VkKeyScanW = reinterpret_cast<decltype(::VkKeyScanW) *>(GetProcAddress(hModule,"VkKeyScanW"));
  this->VkKeyScanExA = reinterpret_cast<decltype(::VkKeyScanExA) *>(GetProcAddress(hModule,"VkKeyScanExA"));
  this->VkKeyScanExW = reinterpret_cast<decltype(::VkKeyScanExW) *>(GetProcAddress(hModule,"VkKeyScanExW"));
  this->keybd_event = reinterpret_cast<decltype(::keybd_event) *>(GetProcAddress(hModule,"keybd_event"));
  this->mouse_event = reinterpret_cast<decltype(::mouse_event) *>(GetProcAddress(hModule,"mouse_event"));
  this->SendInput = reinterpret_cast<decltype(::SendInput) *>(GetProcAddress(hModule,"SendInput"));
  this->GetTouchInputInfo = reinterpret_cast<decltype(::GetTouchInputInfo) *>(GetProcAddress(hModule,"GetTouchInputInfo"));
  this->CloseTouchInputHandle = reinterpret_cast<decltype(::CloseTouchInputHandle) *>(GetProcAddress(hModule,"CloseTouchInputHandle"));
  this->RegisterTouchWindow = reinterpret_cast<decltype(::RegisterTouchWindow) *>(GetProcAddress(hModule,"RegisterTouchWindow"));
  this->UnregisterTouchWindow = reinterpret_cast<decltype(::UnregisterTouchWindow) *>(GetProcAddress(hModule,"UnregisterTouchWindow"));
  this->IsTouchWindow = reinterpret_cast<decltype(::IsTouchWindow) *>(GetProcAddress(hModule,"IsTouchWindow"));
  this->InitializeTouchInjection = reinterpret_cast<decltype(::InitializeTouchInjection) *>(GetProcAddress(hModule,"InitializeTouchInjection"));
  this->InjectTouchInput = reinterpret_cast<decltype(::InjectTouchInput) *>(GetProcAddress(hModule,"InjectTouchInput"));
  this->GetPointerType = reinterpret_cast<decltype(::GetPointerType) *>(GetProcAddress(hModule,"GetPointerType"));
  this->GetPointerCursorId = reinterpret_cast<decltype(::GetPointerCursorId) *>(GetProcAddress(hModule,"GetPointerCursorId"));
  this->GetPointerInfo = reinterpret_cast<decltype(::GetPointerInfo) *>(GetProcAddress(hModule,"GetPointerInfo"));
  this->GetPointerInfoHistory = reinterpret_cast<decltype(::GetPointerInfoHistory) *>(GetProcAddress(hModule,"GetPointerInfoHistory"));
  this->GetPointerFrameInfo = reinterpret_cast<decltype(::GetPointerFrameInfo) *>(GetProcAddress(hModule,"GetPointerFrameInfo"));
  this->GetPointerFrameInfoHistory = reinterpret_cast<decltype(::GetPointerFrameInfoHistory) *>(GetProcAddress(hModule,"GetPointerFrameInfoHistory"));
  this->GetPointerTouchInfo = reinterpret_cast<decltype(::GetPointerTouchInfo) *>(GetProcAddress(hModule,"GetPointerTouchInfo"));
  this->GetPointerTouchInfoHistory = reinterpret_cast<decltype(::GetPointerTouchInfoHistory) *>(GetProcAddress(hModule,"GetPointerTouchInfoHistory"));
  this->GetPointerFrameTouchInfo = reinterpret_cast<decltype(::GetPointerFrameTouchInfo) *>(GetProcAddress(hModule,"GetPointerFrameTouchInfo"));
  this->GetPointerFrameTouchInfoHistory = reinterpret_cast<decltype(::GetPointerFrameTouchInfoHistory) *>(GetProcAddress(hModule,"GetPointerFrameTouchInfoHistory"));
  this->GetPointerPenInfo = reinterpret_cast<decltype(::GetPointerPenInfo) *>(GetProcAddress(hModule,"GetPointerPenInfo"));
  this->GetPointerPenInfoHistory = reinterpret_cast<decltype(::GetPointerPenInfoHistory) *>(GetProcAddress(hModule,"GetPointerPenInfoHistory"));
  this->GetPointerFramePenInfo = reinterpret_cast<decltype(::GetPointerFramePenInfo) *>(GetProcAddress(hModule,"GetPointerFramePenInfo"));
  this->GetPointerFramePenInfoHistory = reinterpret_cast<decltype(::GetPointerFramePenInfoHistory) *>(GetProcAddress(hModule,"GetPointerFramePenInfoHistory"));
  this->SkipPointerFrameMessages = reinterpret_cast<decltype(::SkipPointerFrameMessages) *>(GetProcAddress(hModule,"SkipPointerFrameMessages"));
  this->RegisterPointerInputTarget = reinterpret_cast<decltype(::RegisterPointerInputTarget) *>(GetProcAddress(hModule,"RegisterPointerInputTarget"));
  this->UnregisterPointerInputTarget = reinterpret_cast<decltype(::UnregisterPointerInputTarget) *>(GetProcAddress(hModule,"UnregisterPointerInputTarget"));
  this->EnableMouseInPointer = reinterpret_cast<decltype(::EnableMouseInPointer) *>(GetProcAddress(hModule,"EnableMouseInPointer"));
  this->IsMouseInPointerEnabled = reinterpret_cast<decltype(::IsMouseInPointerEnabled) *>(GetProcAddress(hModule,"IsMouseInPointerEnabled"));
  this->RegisterTouchHitTestingWindow = reinterpret_cast<decltype(::RegisterTouchHitTestingWindow) *>(GetProcAddress(hModule,"RegisterTouchHitTestingWindow"));
  this->EvaluateProximityToRect = reinterpret_cast<decltype(::EvaluateProximityToRect) *>(GetProcAddress(hModule,"EvaluateProximityToRect"));
  this->EvaluateProximityToPolygon = reinterpret_cast<decltype(::EvaluateProximityToPolygon) *>(GetProcAddress(hModule,"EvaluateProximityToPolygon"));
  this->PackTouchHitTestingProximityEvaluation = reinterpret_cast<decltype(::PackTouchHitTestingProximityEvaluation) *>(GetProcAddress(hModule,"PackTouchHitTestingProximityEvaluation"));
  this->GetWindowFeedbackSetting = reinterpret_cast<decltype(::GetWindowFeedbackSetting) *>(GetProcAddress(hModule,"GetWindowFeedbackSetting"));
  this->SetWindowFeedbackSetting = reinterpret_cast<decltype(::SetWindowFeedbackSetting) *>(GetProcAddress(hModule,"SetWindowFeedbackSetting"));
  this->GetLastInputInfo = reinterpret_cast<decltype(::GetLastInputInfo) *>(GetProcAddress(hModule,"GetLastInputInfo"));
  this->MapVirtualKeyA = reinterpret_cast<decltype(::MapVirtualKeyA) *>(GetProcAddress(hModule,"MapVirtualKeyA"));
  this->MapVirtualKeyW = reinterpret_cast<decltype(::MapVirtualKeyW) *>(GetProcAddress(hModule,"MapVirtualKeyW"));
  this->MapVirtualKeyExA = reinterpret_cast<decltype(::MapVirtualKeyExA) *>(GetProcAddress(hModule,"MapVirtualKeyExA"));
  this->MapVirtualKeyExW = reinterpret_cast<decltype(::MapVirtualKeyExW) *>(GetProcAddress(hModule,"MapVirtualKeyExW"));
  this->GetInputState = reinterpret_cast<decltype(::GetInputState) *>(GetProcAddress(hModule,"GetInputState"));
  this->GetQueueStatus = reinterpret_cast<decltype(::GetQueueStatus) *>(GetProcAddress(hModule,"GetQueueStatus"));
  this->GetCapture = reinterpret_cast<decltype(::GetCapture) *>(GetProcAddress(hModule,"GetCapture"));
  this->SetCapture = reinterpret_cast<decltype(::SetCapture) *>(GetProcAddress(hModule,"SetCapture"));
  this->ReleaseCapture = reinterpret_cast<decltype(::ReleaseCapture) *>(GetProcAddress(hModule,"ReleaseCapture"));
  this->MsgWaitForMultipleObjects = reinterpret_cast<decltype(::MsgWaitForMultipleObjects) *>(GetProcAddress(hModule,"MsgWaitForMultipleObjects"));
  this->MsgWaitForMultipleObjectsEx = reinterpret_cast<decltype(::MsgWaitForMultipleObjectsEx) *>(GetProcAddress(hModule,"MsgWaitForMultipleObjectsEx"));
  this->SetTimer = reinterpret_cast<decltype(::SetTimer) *>(GetProcAddress(hModule,"SetTimer"));
  this->KillTimer = reinterpret_cast<decltype(::KillTimer) *>(GetProcAddress(hModule,"KillTimer"));
  this->IsWindowUnicode = reinterpret_cast<decltype(::IsWindowUnicode) *>(GetProcAddress(hModule,"IsWindowUnicode"));
  this->EnableWindow = reinterpret_cast<decltype(::EnableWindow) *>(GetProcAddress(hModule,"EnableWindow"));
  this->IsWindowEnabled = reinterpret_cast<decltype(::IsWindowEnabled) *>(GetProcAddress(hModule,"IsWindowEnabled"));
  this->LoadAcceleratorsA = reinterpret_cast<decltype(::LoadAcceleratorsA) *>(GetProcAddress(hModule,"LoadAcceleratorsA"));
  this->LoadAcceleratorsW = reinterpret_cast<decltype(::LoadAcceleratorsW) *>(GetProcAddress(hModule,"LoadAcceleratorsW"));
  this->CreateAcceleratorTableA = reinterpret_cast<decltype(::CreateAcceleratorTableA) *>(GetProcAddress(hModule,"CreateAcceleratorTableA"));
  this->CreateAcceleratorTableW = reinterpret_cast<decltype(::CreateAcceleratorTableW) *>(GetProcAddress(hModule,"CreateAcceleratorTableW"));
  this->DestroyAcceleratorTable = reinterpret_cast<decltype(::DestroyAcceleratorTable) *>(GetProcAddress(hModule,"DestroyAcceleratorTable"));
  this->CopyAcceleratorTableA = reinterpret_cast<decltype(::CopyAcceleratorTableA) *>(GetProcAddress(hModule,"CopyAcceleratorTableA"));
  this->CopyAcceleratorTableW = reinterpret_cast<decltype(::CopyAcceleratorTableW) *>(GetProcAddress(hModule,"CopyAcceleratorTableW"));
  this->TranslateAcceleratorA = reinterpret_cast<decltype(::TranslateAcceleratorA) *>(GetProcAddress(hModule,"TranslateAcceleratorA"));
  this->TranslateAcceleratorW = reinterpret_cast<decltype(::TranslateAcceleratorW) *>(GetProcAddress(hModule,"TranslateAcceleratorW"));
  this->SetCoalescableTimer = reinterpret_cast<decltype(::SetCoalescableTimer) *>(GetProcAddress(hModule,"SetCoalescableTimer"));
  this->GetSystemMetrics = reinterpret_cast<decltype(::GetSystemMetrics) *>(GetProcAddress(hModule,"GetSystemMetrics"));
  this->LoadMenuA = reinterpret_cast<decltype(::LoadMenuA) *>(GetProcAddress(hModule,"LoadMenuA"));
  this->LoadMenuW = reinterpret_cast<decltype(::LoadMenuW) *>(GetProcAddress(hModule,"LoadMenuW"));
  this->LoadMenuIndirectA = reinterpret_cast<decltype(::LoadMenuIndirectA) *>(GetProcAddress(hModule,"LoadMenuIndirectA"));
  this->LoadMenuIndirectW = reinterpret_cast<decltype(::LoadMenuIndirectW) *>(GetProcAddress(hModule,"LoadMenuIndirectW"));
  this->GetMenu = reinterpret_cast<decltype(::GetMenu) *>(GetProcAddress(hModule,"GetMenu"));
  this->SetMenu = reinterpret_cast<decltype(::SetMenu) *>(GetProcAddress(hModule,"SetMenu"));
  this->ChangeMenuA = reinterpret_cast<decltype(::ChangeMenuA) *>(GetProcAddress(hModule,"ChangeMenuA"));
  this->ChangeMenuW = reinterpret_cast<decltype(::ChangeMenuW) *>(GetProcAddress(hModule,"ChangeMenuW"));
  this->HiliteMenuItem = reinterpret_cast<decltype(::HiliteMenuItem) *>(GetProcAddress(hModule,"HiliteMenuItem"));
  this->GetMenuStringA = reinterpret_cast<decltype(::GetMenuStringA) *>(GetProcAddress(hModule,"GetMenuStringA"));
  this->GetMenuStringW = reinterpret_cast<decltype(::GetMenuStringW) *>(GetProcAddress(hModule,"GetMenuStringW"));
  this->GetMenuState = reinterpret_cast<decltype(::GetMenuState) *>(GetProcAddress(hModule,"GetMenuState"));
  this->DrawMenuBar = reinterpret_cast<decltype(::DrawMenuBar) *>(GetProcAddress(hModule,"DrawMenuBar"));
  this->GetSystemMenu = reinterpret_cast<decltype(::GetSystemMenu) *>(GetProcAddress(hModule,"GetSystemMenu"));
  this->CreateMenu = reinterpret_cast<decltype(::CreateMenu) *>(GetProcAddress(hModule,"CreateMenu"));
  this->CreatePopupMenu = reinterpret_cast<decltype(::CreatePopupMenu) *>(GetProcAddress(hModule,"CreatePopupMenu"));
  this->DestroyMenu = reinterpret_cast<decltype(::DestroyMenu) *>(GetProcAddress(hModule,"DestroyMenu"));
  this->CheckMenuItem = reinterpret_cast<decltype(::CheckMenuItem) *>(GetProcAddress(hModule,"CheckMenuItem"));
  this->EnableMenuItem = reinterpret_cast<decltype(::EnableMenuItem) *>(GetProcAddress(hModule,"EnableMenuItem"));
  this->GetSubMenu = reinterpret_cast<decltype(::GetSubMenu) *>(GetProcAddress(hModule,"GetSubMenu"));
  this->GetMenuItemID = reinterpret_cast<decltype(::GetMenuItemID) *>(GetProcAddress(hModule,"GetMenuItemID"));
  this->GetMenuItemCount = reinterpret_cast<decltype(::GetMenuItemCount) *>(GetProcAddress(hModule,"GetMenuItemCount"));
  this->InsertMenuA = reinterpret_cast<decltype(::InsertMenuA) *>(GetProcAddress(hModule,"InsertMenuA"));
  this->InsertMenuW = reinterpret_cast<decltype(::InsertMenuW) *>(GetProcAddress(hModule,"InsertMenuW"));
  this->AppendMenuA = reinterpret_cast<decltype(::AppendMenuA) *>(GetProcAddress(hModule,"AppendMenuA"));
  this->AppendMenuW = reinterpret_cast<decltype(::AppendMenuW) *>(GetProcAddress(hModule,"AppendMenuW"));
  this->ModifyMenuA = reinterpret_cast<decltype(::ModifyMenuA) *>(GetProcAddress(hModule,"ModifyMenuA"));
  this->ModifyMenuW = reinterpret_cast<decltype(::ModifyMenuW) *>(GetProcAddress(hModule,"ModifyMenuW"));
  this->RemoveMenu = reinterpret_cast<decltype(::RemoveMenu) *>(GetProcAddress(hModule,"RemoveMenu"));
  this->DeleteMenu = reinterpret_cast<decltype(::DeleteMenu) *>(GetProcAddress(hModule,"DeleteMenu"));
  this->SetMenuItemBitmaps = reinterpret_cast<decltype(::SetMenuItemBitmaps) *>(GetProcAddress(hModule,"SetMenuItemBitmaps"));
  this->GetMenuCheckMarkDimensions = reinterpret_cast<decltype(::GetMenuCheckMarkDimensions) *>(GetProcAddress(hModule,"GetMenuCheckMarkDimensions"));
  this->TrackPopupMenu = reinterpret_cast<decltype(::TrackPopupMenu) *>(GetProcAddress(hModule,"TrackPopupMenu"));
  this->TrackPopupMenuEx = reinterpret_cast<decltype(::TrackPopupMenuEx) *>(GetProcAddress(hModule,"TrackPopupMenuEx"));
  this->GetMenuInfo = reinterpret_cast<decltype(::GetMenuInfo) *>(GetProcAddress(hModule,"GetMenuInfo"));
  this->SetMenuInfo = reinterpret_cast<decltype(::SetMenuInfo) *>(GetProcAddress(hModule,"SetMenuInfo"));
  this->EndMenu = reinterpret_cast<decltype(::EndMenu) *>(GetProcAddress(hModule,"EndMenu"));
  this->CalculatePopupWindowPosition = reinterpret_cast<decltype(::CalculatePopupWindowPosition) *>(GetProcAddress(hModule,"CalculatePopupWindowPosition"));
  this->InsertMenuItemA = reinterpret_cast<decltype(::InsertMenuItemA) *>(GetProcAddress(hModule,"InsertMenuItemA"));
  this->InsertMenuItemW = reinterpret_cast<decltype(::InsertMenuItemW) *>(GetProcAddress(hModule,"InsertMenuItemW"));
  this->GetMenuItemInfoA = reinterpret_cast<decltype(::GetMenuItemInfoA) *>(GetProcAddress(hModule,"GetMenuItemInfoA"));
  this->GetMenuItemInfoW = reinterpret_cast<decltype(::GetMenuItemInfoW) *>(GetProcAddress(hModule,"GetMenuItemInfoW"));
  this->SetMenuItemInfoA = reinterpret_cast<decltype(::SetMenuItemInfoA) *>(GetProcAddress(hModule,"SetMenuItemInfoA"));
  this->SetMenuItemInfoW = reinterpret_cast<decltype(::SetMenuItemInfoW) *>(GetProcAddress(hModule,"SetMenuItemInfoW"));
  this->GetMenuDefaultItem = reinterpret_cast<decltype(::GetMenuDefaultItem) *>(GetProcAddress(hModule,"GetMenuDefaultItem"));
  this->SetMenuDefaultItem = reinterpret_cast<decltype(::SetMenuDefaultItem) *>(GetProcAddress(hModule,"SetMenuDefaultItem"));
  this->GetMenuItemRect = reinterpret_cast<decltype(::GetMenuItemRect) *>(GetProcAddress(hModule,"GetMenuItemRect"));
  this->MenuItemFromPoint = reinterpret_cast<decltype(::MenuItemFromPoint) *>(GetProcAddress(hModule,"MenuItemFromPoint"));
  this->DragObject = reinterpret_cast<decltype(::DragObject) *>(GetProcAddress(hModule,"DragObject"));
  this->DragDetect = reinterpret_cast<decltype(::DragDetect) *>(GetProcAddress(hModule,"DragDetect"));
  this->DrawIcon = reinterpret_cast<decltype(::DrawIcon) *>(GetProcAddress(hModule,"DrawIcon"));
  this->DrawTextA = reinterpret_cast<decltype(::DrawTextA) *>(GetProcAddress(hModule,"DrawTextA"));
  this->DrawTextW = reinterpret_cast<decltype(::DrawTextW) *>(GetProcAddress(hModule,"DrawTextW"));
  this->DrawTextExA = reinterpret_cast<decltype(::DrawTextExA) *>(GetProcAddress(hModule,"DrawTextExA"));
  this->DrawTextExW = reinterpret_cast<decltype(::DrawTextExW) *>(GetProcAddress(hModule,"DrawTextExW"));
  this->GrayStringA = reinterpret_cast<decltype(::GrayStringA) *>(GetProcAddress(hModule,"GrayStringA"));
  this->GrayStringW = reinterpret_cast<decltype(::GrayStringW) *>(GetProcAddress(hModule,"GrayStringW"));
  this->DrawStateA = reinterpret_cast<decltype(::DrawStateA) *>(GetProcAddress(hModule,"DrawStateA"));
  this->DrawStateW = reinterpret_cast<decltype(::DrawStateW) *>(GetProcAddress(hModule,"DrawStateW"));
  this->TabbedTextOutA = reinterpret_cast<decltype(::TabbedTextOutA) *>(GetProcAddress(hModule,"TabbedTextOutA"));
  this->TabbedTextOutW = reinterpret_cast<decltype(::TabbedTextOutW) *>(GetProcAddress(hModule,"TabbedTextOutW"));
  this->GetTabbedTextExtentA = reinterpret_cast<decltype(::GetTabbedTextExtentA) *>(GetProcAddress(hModule,"GetTabbedTextExtentA"));
  this->GetTabbedTextExtentW = reinterpret_cast<decltype(::GetTabbedTextExtentW) *>(GetProcAddress(hModule,"GetTabbedTextExtentW"));
  this->UpdateWindow = reinterpret_cast<decltype(::UpdateWindow) *>(GetProcAddress(hModule,"UpdateWindow"));
  this->SetActiveWindow = reinterpret_cast<decltype(::SetActiveWindow) *>(GetProcAddress(hModule,"SetActiveWindow"));
  this->GetForegroundWindow = reinterpret_cast<decltype(::GetForegroundWindow) *>(GetProcAddress(hModule,"GetForegroundWindow"));
  this->PaintDesktop = reinterpret_cast<decltype(::PaintDesktop) *>(GetProcAddress(hModule,"PaintDesktop"));
  this->SwitchToThisWindow = reinterpret_cast<decltype(::SwitchToThisWindow) *>(GetProcAddress(hModule,"SwitchToThisWindow"));
  this->SetForegroundWindow = reinterpret_cast<decltype(::SetForegroundWindow) *>(GetProcAddress(hModule,"SetForegroundWindow"));
  this->AllowSetForegroundWindow = reinterpret_cast<decltype(::AllowSetForegroundWindow) *>(GetProcAddress(hModule,"AllowSetForegroundWindow"));
  this->LockSetForegroundWindow = reinterpret_cast<decltype(::LockSetForegroundWindow) *>(GetProcAddress(hModule,"LockSetForegroundWindow"));
  this->WindowFromDC = reinterpret_cast<decltype(::WindowFromDC) *>(GetProcAddress(hModule,"WindowFromDC"));
  this->GetDC = reinterpret_cast<decltype(::GetDC) *>(GetProcAddress(hModule,"GetDC"));
  this->GetDCEx = reinterpret_cast<decltype(::GetDCEx) *>(GetProcAddress(hModule,"GetDCEx"));
  this->GetWindowDC = reinterpret_cast<decltype(::GetWindowDC) *>(GetProcAddress(hModule,"GetWindowDC"));
  this->ReleaseDC = reinterpret_cast<decltype(::ReleaseDC) *>(GetProcAddress(hModule,"ReleaseDC"));
  this->BeginPaint = reinterpret_cast<decltype(::BeginPaint) *>(GetProcAddress(hModule,"BeginPaint"));
  this->EndPaint = reinterpret_cast<decltype(::EndPaint) *>(GetProcAddress(hModule,"EndPaint"));
  this->GetUpdateRect = reinterpret_cast<decltype(::GetUpdateRect) *>(GetProcAddress(hModule,"GetUpdateRect"));
  this->GetUpdateRgn = reinterpret_cast<decltype(::GetUpdateRgn) *>(GetProcAddress(hModule,"GetUpdateRgn"));
  this->SetWindowRgn = reinterpret_cast<decltype(::SetWindowRgn) *>(GetProcAddress(hModule,"SetWindowRgn"));
  this->GetWindowRgn = reinterpret_cast<decltype(::GetWindowRgn) *>(GetProcAddress(hModule,"GetWindowRgn"));
  this->GetWindowRgnBox = reinterpret_cast<decltype(::GetWindowRgnBox) *>(GetProcAddress(hModule,"GetWindowRgnBox"));
  this->ExcludeUpdateRgn = reinterpret_cast<decltype(::ExcludeUpdateRgn) *>(GetProcAddress(hModule,"ExcludeUpdateRgn"));
  this->InvalidateRect = reinterpret_cast<decltype(::InvalidateRect) *>(GetProcAddress(hModule,"InvalidateRect"));
  this->ValidateRect = reinterpret_cast<decltype(::ValidateRect) *>(GetProcAddress(hModule,"ValidateRect"));
  this->InvalidateRgn = reinterpret_cast<decltype(::InvalidateRgn) *>(GetProcAddress(hModule,"InvalidateRgn"));
  this->ValidateRgn = reinterpret_cast<decltype(::ValidateRgn) *>(GetProcAddress(hModule,"ValidateRgn"));
  this->RedrawWindow = reinterpret_cast<decltype(::RedrawWindow) *>(GetProcAddress(hModule,"RedrawWindow"));
  this->LockWindowUpdate = reinterpret_cast<decltype(::LockWindowUpdate) *>(GetProcAddress(hModule,"LockWindowUpdate"));
  this->ScrollWindow = reinterpret_cast<decltype(::ScrollWindow) *>(GetProcAddress(hModule,"ScrollWindow"));
  this->ScrollDC = reinterpret_cast<decltype(::ScrollDC) *>(GetProcAddress(hModule,"ScrollDC"));
  this->ScrollWindowEx = reinterpret_cast<decltype(::ScrollWindowEx) *>(GetProcAddress(hModule,"ScrollWindowEx"));
  this->SetScrollPos = reinterpret_cast<decltype(::SetScrollPos) *>(GetProcAddress(hModule,"SetScrollPos"));
  this->GetScrollPos = reinterpret_cast<decltype(::GetScrollPos) *>(GetProcAddress(hModule,"GetScrollPos"));
  this->SetScrollRange = reinterpret_cast<decltype(::SetScrollRange) *>(GetProcAddress(hModule,"SetScrollRange"));
  this->GetScrollRange = reinterpret_cast<decltype(::GetScrollRange) *>(GetProcAddress(hModule,"GetScrollRange"));
  this->ShowScrollBar = reinterpret_cast<decltype(::ShowScrollBar) *>(GetProcAddress(hModule,"ShowScrollBar"));
  this->EnableScrollBar = reinterpret_cast<decltype(::EnableScrollBar) *>(GetProcAddress(hModule,"EnableScrollBar"));
  this->SetPropA = reinterpret_cast<decltype(::SetPropA) *>(GetProcAddress(hModule,"SetPropA"));
  this->SetPropW = reinterpret_cast<decltype(::SetPropW) *>(GetProcAddress(hModule,"SetPropW"));
  this->GetPropA = reinterpret_cast<decltype(::GetPropA) *>(GetProcAddress(hModule,"GetPropA"));
  this->GetPropW = reinterpret_cast<decltype(::GetPropW) *>(GetProcAddress(hModule,"GetPropW"));
  this->RemovePropA = reinterpret_cast<decltype(::RemovePropA) *>(GetProcAddress(hModule,"RemovePropA"));
  this->RemovePropW = reinterpret_cast<decltype(::RemovePropW) *>(GetProcAddress(hModule,"RemovePropW"));
  this->EnumPropsExA = reinterpret_cast<decltype(::EnumPropsExA) *>(GetProcAddress(hModule,"EnumPropsExA"));
  this->EnumPropsExW = reinterpret_cast<decltype(::EnumPropsExW) *>(GetProcAddress(hModule,"EnumPropsExW"));
  this->EnumPropsA = reinterpret_cast<decltype(::EnumPropsA) *>(GetProcAddress(hModule,"EnumPropsA"));
  this->EnumPropsW = reinterpret_cast<decltype(::EnumPropsW) *>(GetProcAddress(hModule,"EnumPropsW"));
  this->SetWindowTextA = reinterpret_cast<decltype(::SetWindowTextA) *>(GetProcAddress(hModule,"SetWindowTextA"));
  this->SetWindowTextW = reinterpret_cast<decltype(::SetWindowTextW) *>(GetProcAddress(hModule,"SetWindowTextW"));
  this->GetWindowTextA = reinterpret_cast<decltype(::GetWindowTextA) *>(GetProcAddress(hModule,"GetWindowTextA"));
  this->GetWindowTextW = reinterpret_cast<decltype(::GetWindowTextW) *>(GetProcAddress(hModule,"GetWindowTextW"));
  this->GetWindowTextLengthA = reinterpret_cast<decltype(::GetWindowTextLengthA) *>(GetProcAddress(hModule,"GetWindowTextLengthA"));
  this->GetWindowTextLengthW = reinterpret_cast<decltype(::GetWindowTextLengthW) *>(GetProcAddress(hModule,"GetWindowTextLengthW"));
  this->GetClientRect = reinterpret_cast<decltype(::GetClientRect) *>(GetProcAddress(hModule,"GetClientRect"));
  this->GetWindowRect = reinterpret_cast<decltype(::GetWindowRect) *>(GetProcAddress(hModule,"GetWindowRect"));
  this->AdjustWindowRect = reinterpret_cast<decltype(::AdjustWindowRect) *>(GetProcAddress(hModule,"AdjustWindowRect"));
  this->AdjustWindowRectEx = reinterpret_cast<decltype(::AdjustWindowRectEx) *>(GetProcAddress(hModule,"AdjustWindowRectEx"));
  this->SetWindowContextHelpId = reinterpret_cast<decltype(::SetWindowContextHelpId) *>(GetProcAddress(hModule,"SetWindowContextHelpId"));
  this->GetWindowContextHelpId = reinterpret_cast<decltype(::GetWindowContextHelpId) *>(GetProcAddress(hModule,"GetWindowContextHelpId"));
  this->SetMenuContextHelpId = reinterpret_cast<decltype(::SetMenuContextHelpId) *>(GetProcAddress(hModule,"SetMenuContextHelpId"));
  this->GetMenuContextHelpId = reinterpret_cast<decltype(::GetMenuContextHelpId) *>(GetProcAddress(hModule,"GetMenuContextHelpId"));
  this->MessageBoxA = reinterpret_cast<decltype(::MessageBoxA) *>(GetProcAddress(hModule,"MessageBoxA"));
  this->MessageBoxW = reinterpret_cast<decltype(::MessageBoxW) *>(GetProcAddress(hModule,"MessageBoxW"));
  this->MessageBoxExA = reinterpret_cast<decltype(::MessageBoxExA) *>(GetProcAddress(hModule,"MessageBoxExA"));
  this->MessageBoxExW = reinterpret_cast<decltype(::MessageBoxExW) *>(GetProcAddress(hModule,"MessageBoxExW"));
  this->MessageBoxIndirectA = reinterpret_cast<decltype(::MessageBoxIndirectA) *>(GetProcAddress(hModule,"MessageBoxIndirectA"));
  this->MessageBoxIndirectW = reinterpret_cast<decltype(::MessageBoxIndirectW) *>(GetProcAddress(hModule,"MessageBoxIndirectW"));
  this->MessageBeep = reinterpret_cast<decltype(::MessageBeep) *>(GetProcAddress(hModule,"MessageBeep"));
  this->ShowCursor = reinterpret_cast<decltype(::ShowCursor) *>(GetProcAddress(hModule,"ShowCursor"));
  this->SetCursorPos = reinterpret_cast<decltype(::SetCursorPos) *>(GetProcAddress(hModule,"SetCursorPos"));
  this->SetCursor = reinterpret_cast<decltype(::SetCursor) *>(GetProcAddress(hModule,"SetCursor"));
  this->GetCursorPos = reinterpret_cast<decltype(::GetCursorPos) *>(GetProcAddress(hModule,"GetCursorPos"));
  this->ClipCursor = reinterpret_cast<decltype(::ClipCursor) *>(GetProcAddress(hModule,"ClipCursor"));
  this->GetClipCursor = reinterpret_cast<decltype(::GetClipCursor) *>(GetProcAddress(hModule,"GetClipCursor"));
  this->GetCursor = reinterpret_cast<decltype(::GetCursor) *>(GetProcAddress(hModule,"GetCursor"));
  this->CreateCaret = reinterpret_cast<decltype(::CreateCaret) *>(GetProcAddress(hModule,"CreateCaret"));
  this->GetCaretBlinkTime = reinterpret_cast<decltype(::GetCaretBlinkTime) *>(GetProcAddress(hModule,"GetCaretBlinkTime"));
  this->SetCaretBlinkTime = reinterpret_cast<decltype(::SetCaretBlinkTime) *>(GetProcAddress(hModule,"SetCaretBlinkTime"));
  this->DestroyCaret = reinterpret_cast<decltype(::DestroyCaret) *>(GetProcAddress(hModule,"DestroyCaret"));
  this->HideCaret = reinterpret_cast<decltype(::HideCaret) *>(GetProcAddress(hModule,"HideCaret"));
  this->ShowCaret = reinterpret_cast<decltype(::ShowCaret) *>(GetProcAddress(hModule,"ShowCaret"));
  this->SetCaretPos = reinterpret_cast<decltype(::SetCaretPos) *>(GetProcAddress(hModule,"SetCaretPos"));
  this->GetCaretPos = reinterpret_cast<decltype(::GetCaretPos) *>(GetProcAddress(hModule,"GetCaretPos"));
  this->ClientToScreen = reinterpret_cast<decltype(::ClientToScreen) *>(GetProcAddress(hModule,"ClientToScreen"));
  this->ScreenToClient = reinterpret_cast<decltype(::ScreenToClient) *>(GetProcAddress(hModule,"ScreenToClient"));
  this->MapWindowPoints = reinterpret_cast<decltype(::MapWindowPoints) *>(GetProcAddress(hModule,"MapWindowPoints"));
  this->WindowFromPoint = reinterpret_cast<decltype(::WindowFromPoint) *>(GetProcAddress(hModule,"WindowFromPoint"));
  this->ChildWindowFromPoint = reinterpret_cast<decltype(::ChildWindowFromPoint) *>(GetProcAddress(hModule,"ChildWindowFromPoint"));
  this->ChildWindowFromPointEx = reinterpret_cast<decltype(::ChildWindowFromPointEx) *>(GetProcAddress(hModule,"ChildWindowFromPointEx"));
  this->SetPhysicalCursorPos = reinterpret_cast<decltype(::SetPhysicalCursorPos) *>(GetProcAddress(hModule,"SetPhysicalCursorPos"));
  this->GetPhysicalCursorPos = reinterpret_cast<decltype(::GetPhysicalCursorPos) *>(GetProcAddress(hModule,"GetPhysicalCursorPos"));
  this->LogicalToPhysicalPoint = reinterpret_cast<decltype(::LogicalToPhysicalPoint) *>(GetProcAddress(hModule,"LogicalToPhysicalPoint"));
  this->PhysicalToLogicalPoint = reinterpret_cast<decltype(::PhysicalToLogicalPoint) *>(GetProcAddress(hModule,"PhysicalToLogicalPoint"));
  this->WindowFromPhysicalPoint = reinterpret_cast<decltype(::WindowFromPhysicalPoint) *>(GetProcAddress(hModule,"WindowFromPhysicalPoint"));
  this->GetSysColor = reinterpret_cast<decltype(::GetSysColor) *>(GetProcAddress(hModule,"GetSysColor"));
  this->GetSysColorBrush = reinterpret_cast<decltype(::GetSysColorBrush) *>(GetProcAddress(hModule,"GetSysColorBrush"));
  this->SetSysColors = reinterpret_cast<decltype(::SetSysColors) *>(GetProcAddress(hModule,"SetSysColors"));
  this->DrawFocusRect = reinterpret_cast<decltype(::DrawFocusRect) *>(GetProcAddress(hModule,"DrawFocusRect"));
  this->FillRect = reinterpret_cast<decltype(::FillRect) *>(GetProcAddress(hModule,"FillRect"));
  this->FrameRect = reinterpret_cast<decltype(::FrameRect) *>(GetProcAddress(hModule,"FrameRect"));
  this->InvertRect = reinterpret_cast<decltype(::InvertRect) *>(GetProcAddress(hModule,"InvertRect"));
  this->SetRect = reinterpret_cast<decltype(::SetRect) *>(GetProcAddress(hModule,"SetRect"));
  this->SetRectEmpty = reinterpret_cast<decltype(::SetRectEmpty) *>(GetProcAddress(hModule,"SetRectEmpty"));
  this->CopyRect = reinterpret_cast<decltype(::CopyRect) *>(GetProcAddress(hModule,"CopyRect"));
  this->InflateRect = reinterpret_cast<decltype(::InflateRect) *>(GetProcAddress(hModule,"InflateRect"));
  this->IntersectRect = reinterpret_cast<decltype(::IntersectRect) *>(GetProcAddress(hModule,"IntersectRect"));
  this->UnionRect = reinterpret_cast<decltype(::UnionRect) *>(GetProcAddress(hModule,"UnionRect"));
  this->SubtractRect = reinterpret_cast<decltype(::SubtractRect) *>(GetProcAddress(hModule,"SubtractRect"));
  this->OffsetRect = reinterpret_cast<decltype(::OffsetRect) *>(GetProcAddress(hModule,"OffsetRect"));
  this->IsRectEmpty = reinterpret_cast<decltype(::IsRectEmpty) *>(GetProcAddress(hModule,"IsRectEmpty"));
  this->EqualRect = reinterpret_cast<decltype(::EqualRect) *>(GetProcAddress(hModule,"EqualRect"));
  this->PtInRect = reinterpret_cast<decltype(::PtInRect) *>(GetProcAddress(hModule,"PtInRect"));
  this->GetWindowWord = reinterpret_cast<decltype(::GetWindowWord) *>(GetProcAddress(hModule,"GetWindowWord"));
  this->SetWindowWord = reinterpret_cast<decltype(::SetWindowWord) *>(GetProcAddress(hModule,"SetWindowWord"));
  this->GetWindowLongA = reinterpret_cast<decltype(::GetWindowLongA) *>(GetProcAddress(hModule,"GetWindowLongA"));
  this->GetWindowLongW = reinterpret_cast<decltype(::GetWindowLongW) *>(GetProcAddress(hModule,"GetWindowLongW"));
  this->SetWindowLongA = reinterpret_cast<decltype(::SetWindowLongA) *>(GetProcAddress(hModule,"SetWindowLongA"));
  this->SetWindowLongW = reinterpret_cast<decltype(::SetWindowLongW) *>(GetProcAddress(hModule,"SetWindowLongW"));
#ifdef _WIN64
  this->GetWindowLongPtrA = reinterpret_cast<decltype(::GetWindowLongPtrA) *>(GetProcAddress(hModule,"GetWindowLongPtrA"));
  this->GetWindowLongPtrW = reinterpret_cast<decltype(::GetWindowLongPtrW) *>(GetProcAddress(hModule,"GetWindowLongPtrW"));
  this->SetWindowLongPtrA = reinterpret_cast<decltype(::SetWindowLongPtrA) *>(GetProcAddress(hModule,"SetWindowLongPtrA"));
  this->SetWindowLongPtrW = reinterpret_cast<decltype(::SetWindowLongPtrW) *>(GetProcAddress(hModule,"SetWindowLongPtrW"));
#endif
  this->GetClassWord = reinterpret_cast<decltype(::GetClassWord) *>(GetProcAddress(hModule,"GetClassWord"));
  this->SetClassWord = reinterpret_cast<decltype(::SetClassWord) *>(GetProcAddress(hModule,"SetClassWord"));
  this->GetClassLongA = reinterpret_cast<decltype(::GetClassLongA) *>(GetProcAddress(hModule,"GetClassLongA"));
  this->GetClassLongW = reinterpret_cast<decltype(::GetClassLongW) *>(GetProcAddress(hModule,"GetClassLongW"));
  this->SetClassLongA = reinterpret_cast<decltype(::SetClassLongA) *>(GetProcAddress(hModule,"SetClassLongA"));
  this->SetClassLongW = reinterpret_cast<decltype(::SetClassLongW) *>(GetProcAddress(hModule,"SetClassLongW"));
#ifdef _WIN64
  this->GetClassLongPtrA = reinterpret_cast<decltype(::GetClassLongPtrA) *>(GetProcAddress(hModule,"GetClassLongPtrA"));
  this->GetClassLongPtrW = reinterpret_cast<decltype(::GetClassLongPtrW) *>(GetProcAddress(hModule,"GetClassLongPtrW"));
  this->SetClassLongPtrA = reinterpret_cast<decltype(::SetClassLongPtrA) *>(GetProcAddress(hModule,"SetClassLongPtrA"));
  this->SetClassLongPtrW = reinterpret_cast<decltype(::SetClassLongPtrW) *>(GetProcAddress(hModule,"SetClassLongPtrW"));
#endif
  this->GetProcessDefaultLayout = reinterpret_cast<decltype(::GetProcessDefaultLayout) *>(GetProcAddress(hModule,"GetProcessDefaultLayout"));
  this->SetProcessDefaultLayout = reinterpret_cast<decltype(::SetProcessDefaultLayout) *>(GetProcAddress(hModule,"SetProcessDefaultLayout"));
  this->GetDesktopWindow = reinterpret_cast<decltype(::GetDesktopWindow) *>(GetProcAddress(hModule,"GetDesktopWindow"));
  this->GetParent = reinterpret_cast<decltype(::GetParent) *>(GetProcAddress(hModule,"GetParent"));
  this->SetParent = reinterpret_cast<decltype(::SetParent) *>(GetProcAddress(hModule,"SetParent"));
  this->EnumChildWindows = reinterpret_cast<decltype(::EnumChildWindows) *>(GetProcAddress(hModule,"EnumChildWindows"));
  this->FindWindowA = reinterpret_cast<decltype(::FindWindowA) *>(GetProcAddress(hModule,"FindWindowA"));
  this->FindWindowW = reinterpret_cast<decltype(::FindWindowW) *>(GetProcAddress(hModule,"FindWindowW"));
  this->FindWindowExA = reinterpret_cast<decltype(::FindWindowExA) *>(GetProcAddress(hModule,"FindWindowExA"));
  this->FindWindowExW = reinterpret_cast<decltype(::FindWindowExW) *>(GetProcAddress(hModule,"FindWindowExW"));
  this->GetShellWindow = reinterpret_cast<decltype(::GetShellWindow) *>(GetProcAddress(hModule,"GetShellWindow"));
  this->RegisterShellHookWindow = reinterpret_cast<decltype(::RegisterShellHookWindow) *>(GetProcAddress(hModule,"RegisterShellHookWindow"));
  this->DeregisterShellHookWindow = reinterpret_cast<decltype(::DeregisterShellHookWindow) *>(GetProcAddress(hModule,"DeregisterShellHookWindow"));
  this->EnumWindows = reinterpret_cast<decltype(::EnumWindows) *>(GetProcAddress(hModule,"EnumWindows"));
  this->EnumThreadWindows = reinterpret_cast<decltype(::EnumThreadWindows) *>(GetProcAddress(hModule,"EnumThreadWindows"));
  this->GetClassNameA = reinterpret_cast<decltype(::GetClassNameA) *>(GetProcAddress(hModule,"GetClassNameA"));
  this->GetClassNameW = reinterpret_cast<decltype(::GetClassNameW) *>(GetProcAddress(hModule,"GetClassNameW"));
  this->GetTopWindow = reinterpret_cast<decltype(::GetTopWindow) *>(GetProcAddress(hModule,"GetTopWindow"));
  this->GetWindowThreadProcessId = reinterpret_cast<decltype(::GetWindowThreadProcessId) *>(GetProcAddress(hModule,"GetWindowThreadProcessId"));
  this->IsGUIThread = reinterpret_cast<decltype(::IsGUIThread) *>(GetProcAddress(hModule,"IsGUIThread"));
  this->GetLastActivePopup = reinterpret_cast<decltype(::GetLastActivePopup) *>(GetProcAddress(hModule,"GetLastActivePopup"));
  this->GetWindow = reinterpret_cast<decltype(::GetWindow) *>(GetProcAddress(hModule,"GetWindow"));
  this->SetWindowsHookA = reinterpret_cast<decltype(::SetWindowsHookA) *>(GetProcAddress(hModule,"SetWindowsHookA"));
  this->SetWindowsHookW = reinterpret_cast<decltype(::SetWindowsHookW) *>(GetProcAddress(hModule,"SetWindowsHookW"));
  this->UnhookWindowsHook = reinterpret_cast<decltype(::UnhookWindowsHook) *>(GetProcAddress(hModule,"UnhookWindowsHook"));
  this->SetWindowsHookExA = reinterpret_cast<decltype(::SetWindowsHookExA) *>(GetProcAddress(hModule,"SetWindowsHookExA"));
  this->SetWindowsHookExW = reinterpret_cast<decltype(::SetWindowsHookExW) *>(GetProcAddress(hModule,"SetWindowsHookExW"));
  this->UnhookWindowsHookEx = reinterpret_cast<decltype(::UnhookWindowsHookEx) *>(GetProcAddress(hModule,"UnhookWindowsHookEx"));
  this->CallNextHookEx = reinterpret_cast<decltype(::CallNextHookEx) *>(GetProcAddress(hModule,"CallNextHookEx"));
  this->CheckMenuRadioItem = reinterpret_cast<decltype(::CheckMenuRadioItem) *>(GetProcAddress(hModule,"CheckMenuRadioItem"));
  this->LoadBitmapA = reinterpret_cast<decltype(::LoadBitmapA) *>(GetProcAddress(hModule,"LoadBitmapA"));
  this->LoadBitmapW = reinterpret_cast<decltype(::LoadBitmapW) *>(GetProcAddress(hModule,"LoadBitmapW"));
  this->LoadCursorA = reinterpret_cast<decltype(::LoadCursorA) *>(GetProcAddress(hModule,"LoadCursorA"));
  this->LoadCursorW = reinterpret_cast<decltype(::LoadCursorW) *>(GetProcAddress(hModule,"LoadCursorW"));
  this->LoadCursorFromFileA = reinterpret_cast<decltype(::LoadCursorFromFileA) *>(GetProcAddress(hModule,"LoadCursorFromFileA"));
  this->LoadCursorFromFileW = reinterpret_cast<decltype(::LoadCursorFromFileW) *>(GetProcAddress(hModule,"LoadCursorFromFileW"));
  this->CreateCursor = reinterpret_cast<decltype(::CreateCursor) *>(GetProcAddress(hModule,"CreateCursor"));
  this->DestroyCursor = reinterpret_cast<decltype(::DestroyCursor) *>(GetProcAddress(hModule,"DestroyCursor"));
  this->SetSystemCursor = reinterpret_cast<decltype(::SetSystemCursor) *>(GetProcAddress(hModule,"SetSystemCursor"));
  this->LoadIconA = reinterpret_cast<decltype(::LoadIconA) *>(GetProcAddress(hModule,"LoadIconA"));
  this->LoadIconW = reinterpret_cast<decltype(::LoadIconW) *>(GetProcAddress(hModule,"LoadIconW"));
  this->PrivateExtractIconsA = reinterpret_cast<decltype(::PrivateExtractIconsA) *>(GetProcAddress(hModule,"PrivateExtractIconsA"));
  this->PrivateExtractIconsW = reinterpret_cast<decltype(::PrivateExtractIconsW) *>(GetProcAddress(hModule,"PrivateExtractIconsW"));
  this->CreateIcon = reinterpret_cast<decltype(::CreateIcon) *>(GetProcAddress(hModule,"CreateIcon"));
  this->DestroyIcon = reinterpret_cast<decltype(::DestroyIcon) *>(GetProcAddress(hModule,"DestroyIcon"));
  this->LookupIconIdFromDirectory = reinterpret_cast<decltype(::LookupIconIdFromDirectory) *>(GetProcAddress(hModule,"LookupIconIdFromDirectory"));
  this->LookupIconIdFromDirectoryEx = reinterpret_cast<decltype(::LookupIconIdFromDirectoryEx) *>(GetProcAddress(hModule,"LookupIconIdFromDirectoryEx"));
  this->CreateIconFromResource = reinterpret_cast<decltype(::CreateIconFromResource) *>(GetProcAddress(hModule,"CreateIconFromResource"));
  this->CreateIconFromResourceEx = reinterpret_cast<decltype(::CreateIconFromResourceEx) *>(GetProcAddress(hModule,"CreateIconFromResourceEx"));
  this->LoadImageA = reinterpret_cast<decltype(::LoadImageA) *>(GetProcAddress(hModule,"LoadImageA"));
  this->LoadImageW = reinterpret_cast<decltype(::LoadImageW) *>(GetProcAddress(hModule,"LoadImageW"));
  this->CopyImage = reinterpret_cast<decltype(::CopyImage) *>(GetProcAddress(hModule,"CopyImage"));
  this->DrawIconEx = reinterpret_cast<decltype(::DrawIconEx) *>(GetProcAddress(hModule,"DrawIconEx"));
  this->CreateIconIndirect = reinterpret_cast<decltype(::CreateIconIndirect) *>(GetProcAddress(hModule,"CreateIconIndirect"));
  this->CopyIcon = reinterpret_cast<decltype(::CopyIcon) *>(GetProcAddress(hModule,"CopyIcon"));
  this->GetIconInfo = reinterpret_cast<decltype(::GetIconInfo) *>(GetProcAddress(hModule,"GetIconInfo"));
  this->GetIconInfoExA = reinterpret_cast<decltype(::GetIconInfoExA) *>(GetProcAddress(hModule,"GetIconInfoExA"));
  this->GetIconInfoExW = reinterpret_cast<decltype(::GetIconInfoExW) *>(GetProcAddress(hModule,"GetIconInfoExW"));
  this->LoadStringA = reinterpret_cast<decltype(::LoadStringA) *>(GetProcAddress(hModule,"LoadStringA"));
  this->LoadStringW = reinterpret_cast<decltype(::LoadStringW) *>(GetProcAddress(hModule,"LoadStringW"));
  this->IsDialogMessageA = reinterpret_cast<decltype(::IsDialogMessageA) *>(GetProcAddress(hModule,"IsDialogMessageA"));
  this->IsDialogMessageW = reinterpret_cast<decltype(::IsDialogMessageW) *>(GetProcAddress(hModule,"IsDialogMessageW"));
  this->MapDialogRect = reinterpret_cast<decltype(::MapDialogRect) *>(GetProcAddress(hModule,"MapDialogRect"));
  this->DlgDirListA = reinterpret_cast<decltype(::DlgDirListA) *>(GetProcAddress(hModule,"DlgDirListA"));
  this->DlgDirListW = reinterpret_cast<decltype(::DlgDirListW) *>(GetProcAddress(hModule,"DlgDirListW"));
  this->DlgDirSelectExA = reinterpret_cast<decltype(::DlgDirSelectExA) *>(GetProcAddress(hModule,"DlgDirSelectExA"));
  this->DlgDirSelectExW = reinterpret_cast<decltype(::DlgDirSelectExW) *>(GetProcAddress(hModule,"DlgDirSelectExW"));
  this->DlgDirListComboBoxA = reinterpret_cast<decltype(::DlgDirListComboBoxA) *>(GetProcAddress(hModule,"DlgDirListComboBoxA"));
  this->DlgDirListComboBoxW = reinterpret_cast<decltype(::DlgDirListComboBoxW) *>(GetProcAddress(hModule,"DlgDirListComboBoxW"));
  this->DlgDirSelectComboBoxExA = reinterpret_cast<decltype(::DlgDirSelectComboBoxExA) *>(GetProcAddress(hModule,"DlgDirSelectComboBoxExA"));
  this->DlgDirSelectComboBoxExW = reinterpret_cast<decltype(::DlgDirSelectComboBoxExW) *>(GetProcAddress(hModule,"DlgDirSelectComboBoxExW"));
  this->SetScrollInfo = reinterpret_cast<decltype(::SetScrollInfo) *>(GetProcAddress(hModule,"SetScrollInfo"));
  this->GetScrollInfo = reinterpret_cast<decltype(::GetScrollInfo) *>(GetProcAddress(hModule,"GetScrollInfo"));
  this->DefFrameProcA = reinterpret_cast<decltype(::DefFrameProcA) *>(GetProcAddress(hModule,"DefFrameProcA"));
  this->DefFrameProcW = reinterpret_cast<decltype(::DefFrameProcW) *>(GetProcAddress(hModule,"DefFrameProcW"));
  this->DefMDIChildProcA = reinterpret_cast<decltype(::DefMDIChildProcA) *>(GetProcAddress(hModule,"DefMDIChildProcA"));
  this->DefMDIChildProcW = reinterpret_cast<decltype(::DefMDIChildProcW) *>(GetProcAddress(hModule,"DefMDIChildProcW"));
  this->TranslateMDISysAccel = reinterpret_cast<decltype(::TranslateMDISysAccel) *>(GetProcAddress(hModule,"TranslateMDISysAccel"));
  this->ArrangeIconicWindows = reinterpret_cast<decltype(::ArrangeIconicWindows) *>(GetProcAddress(hModule,"ArrangeIconicWindows"));
  this->CreateMDIWindowA = reinterpret_cast<decltype(::CreateMDIWindowA) *>(GetProcAddress(hModule,"CreateMDIWindowA"));
  this->CreateMDIWindowW = reinterpret_cast<decltype(::CreateMDIWindowW) *>(GetProcAddress(hModule,"CreateMDIWindowW"));
  this->TileWindows = reinterpret_cast<decltype(::TileWindows) *>(GetProcAddress(hModule,"TileWindows"));
  this->CascadeWindows = reinterpret_cast<decltype(::CascadeWindows) *>(GetProcAddress(hModule,"CascadeWindows"));
  this->WinHelpA = reinterpret_cast<decltype(::WinHelpA) *>(GetProcAddress(hModule,"WinHelpA"));
  this->WinHelpW = reinterpret_cast<decltype(::WinHelpW) *>(GetProcAddress(hModule,"WinHelpW"));
  this->GetGuiResources = reinterpret_cast<decltype(::GetGuiResources) *>(GetProcAddress(hModule,"GetGuiResources"));
  this->ChangeDisplaySettingsA = reinterpret_cast<decltype(::ChangeDisplaySettingsA) *>(GetProcAddress(hModule,"ChangeDisplaySettingsA"));
  this->ChangeDisplaySettingsW = reinterpret_cast<decltype(::ChangeDisplaySettingsW) *>(GetProcAddress(hModule,"ChangeDisplaySettingsW"));
  this->ChangeDisplaySettingsExA = reinterpret_cast<decltype(::ChangeDisplaySettingsExA) *>(GetProcAddress(hModule,"ChangeDisplaySettingsExA"));
  this->ChangeDisplaySettingsExW = reinterpret_cast<decltype(::ChangeDisplaySettingsExW) *>(GetProcAddress(hModule,"ChangeDisplaySettingsExW"));
  this->EnumDisplaySettingsA = reinterpret_cast<decltype(::EnumDisplaySettingsA) *>(GetProcAddress(hModule,"EnumDisplaySettingsA"));
  this->EnumDisplaySettingsW = reinterpret_cast<decltype(::EnumDisplaySettingsW) *>(GetProcAddress(hModule,"EnumDisplaySettingsW"));
  this->EnumDisplaySettingsExA = reinterpret_cast<decltype(::EnumDisplaySettingsExA) *>(GetProcAddress(hModule,"EnumDisplaySettingsExA"));
  this->EnumDisplaySettingsExW = reinterpret_cast<decltype(::EnumDisplaySettingsExW) *>(GetProcAddress(hModule,"EnumDisplaySettingsExW"));
  this->EnumDisplayDevicesA = reinterpret_cast<decltype(::EnumDisplayDevicesA) *>(GetProcAddress(hModule,"EnumDisplayDevicesA"));
  this->EnumDisplayDevicesW = reinterpret_cast<decltype(::EnumDisplayDevicesW) *>(GetProcAddress(hModule,"EnumDisplayDevicesW"));
  this->GetDisplayConfigBufferSizes = reinterpret_cast<decltype(::GetDisplayConfigBufferSizes) *>(GetProcAddress(hModule,"GetDisplayConfigBufferSizes"));
  this->SetDisplayConfig = reinterpret_cast<decltype(::SetDisplayConfig) *>(GetProcAddress(hModule,"SetDisplayConfig"));
  this->QueryDisplayConfig = reinterpret_cast<decltype(::QueryDisplayConfig) *>(GetProcAddress(hModule,"QueryDisplayConfig"));
  this->DisplayConfigGetDeviceInfo = reinterpret_cast<decltype(::DisplayConfigGetDeviceInfo) *>(GetProcAddress(hModule,"DisplayConfigGetDeviceInfo"));
  this->DisplayConfigSetDeviceInfo = reinterpret_cast<decltype(::DisplayConfigSetDeviceInfo) *>(GetProcAddress(hModule,"DisplayConfigSetDeviceInfo"));
  this->SystemParametersInfoA = reinterpret_cast<decltype(::SystemParametersInfoA) *>(GetProcAddress(hModule,"SystemParametersInfoA"));
  this->SystemParametersInfoW = reinterpret_cast<decltype(::SystemParametersInfoW) *>(GetProcAddress(hModule,"SystemParametersInfoW"));
  this->SetDebugErrorLevel = reinterpret_cast<decltype(::SetDebugErrorLevel) *>(GetProcAddress(hModule,"SetDebugErrorLevel"));
  this->SetLastErrorEx = reinterpret_cast<decltype(::SetLastErrorEx) *>(GetProcAddress(hModule,"SetLastErrorEx"));
  this->InternalGetWindowText = reinterpret_cast<decltype(::InternalGetWindowText) *>(GetProcAddress(hModule,"InternalGetWindowText"));
  this->CancelShutdown = reinterpret_cast<decltype(::CancelShutdown) *>(GetProcAddress(hModule,"CancelShutdown"));
  this->MonitorFromPoint = reinterpret_cast<decltype(::MonitorFromPoint) *>(GetProcAddress(hModule,"MonitorFromPoint"));
  this->MonitorFromRect = reinterpret_cast<decltype(::MonitorFromRect) *>(GetProcAddress(hModule,"MonitorFromRect"));
  this->MonitorFromWindow = reinterpret_cast<decltype(::MonitorFromWindow) *>(GetProcAddress(hModule,"MonitorFromWindow"));
#ifdef WINNT
  this->EndTask = reinterpret_cast<decltype(::EndTask) *>(GetProcAddress(hModule,"EndTask"));
#endif
  this->SoundSentry = reinterpret_cast<decltype(::SoundSentry) *>(GetProcAddress(hModule,"SoundSentry"));
  this->GetMonitorInfoA = reinterpret_cast<decltype(::GetMonitorInfoA) *>(GetProcAddress(hModule,"GetMonitorInfoA"));
  this->GetMonitorInfoW = reinterpret_cast<decltype(::GetMonitorInfoW) *>(GetProcAddress(hModule,"GetMonitorInfoW"));
  this->EnumDisplayMonitors = reinterpret_cast<decltype(::EnumDisplayMonitors) *>(GetProcAddress(hModule,"EnumDisplayMonitors"));
  this->NotifyWinEvent = reinterpret_cast<decltype(::NotifyWinEvent) *>(GetProcAddress(hModule,"NotifyWinEvent"));
  this->SetWinEventHook = reinterpret_cast<decltype(::SetWinEventHook) *>(GetProcAddress(hModule,"SetWinEventHook"));
  this->IsWinEventHookInstalled = reinterpret_cast<decltype(::IsWinEventHookInstalled) *>(GetProcAddress(hModule,"IsWinEventHookInstalled"));
  this->UnhookWinEvent = reinterpret_cast<decltype(::UnhookWinEvent) *>(GetProcAddress(hModule,"UnhookWinEvent"));
  this->GetGUIThreadInfo = reinterpret_cast<decltype(::GetGUIThreadInfo) *>(GetProcAddress(hModule,"GetGUIThreadInfo"));
  this->BlockInput = reinterpret_cast<decltype(::BlockInput) *>(GetProcAddress(hModule,"BlockInput"));
  this->GetWindowModuleFileNameA = reinterpret_cast<decltype(::GetWindowModuleFileNameA) *>(GetProcAddress(hModule,"GetWindowModuleFileNameA"));
  this->GetWindowModuleFileNameW = reinterpret_cast<decltype(::GetWindowModuleFileNameW) *>(GetProcAddress(hModule,"GetWindowModuleFileNameW"));
  this->SetProcessDPIAware = reinterpret_cast<decltype(::SetProcessDPIAware) *>(GetProcAddress(hModule,"SetProcessDPIAware"));
  this->IsProcessDPIAware = reinterpret_cast<decltype(::IsProcessDPIAware) *>(GetProcAddress(hModule,"IsProcessDPIAware"));
  this->GetCursorInfo = reinterpret_cast<decltype(::GetCursorInfo) *>(GetProcAddress(hModule,"GetCursorInfo"));
  this->GetWindowInfo = reinterpret_cast<decltype(::GetWindowInfo) *>(GetProcAddress(hModule,"GetWindowInfo"));
  this->GetTitleBarInfo = reinterpret_cast<decltype(::GetTitleBarInfo) *>(GetProcAddress(hModule,"GetTitleBarInfo"));
  this->GetMenuBarInfo = reinterpret_cast<decltype(::GetMenuBarInfo) *>(GetProcAddress(hModule,"GetMenuBarInfo"));
  this->GetScrollBarInfo = reinterpret_cast<decltype(::GetScrollBarInfo) *>(GetProcAddress(hModule,"GetScrollBarInfo"));
  this->GetComboBoxInfo = reinterpret_cast<decltype(::GetComboBoxInfo) *>(GetProcAddress(hModule,"GetComboBoxInfo"));
  this->GetAncestor = reinterpret_cast<decltype(::GetAncestor) *>(GetProcAddress(hModule,"GetAncestor"));
  this->RealChildWindowFromPoint = reinterpret_cast<decltype(::RealChildWindowFromPoint) *>(GetProcAddress(hModule,"RealChildWindowFromPoint"));
  this->RealGetWindowClassA = reinterpret_cast<decltype(::RealGetWindowClassA) *>(GetProcAddress(hModule,"RealGetWindowClassA"));
  this->RealGetWindowClassW = reinterpret_cast<decltype(::RealGetWindowClassW) *>(GetProcAddress(hModule,"RealGetWindowClassW"));
  this->GetAltTabInfoA = reinterpret_cast<decltype(::GetAltTabInfoA) *>(GetProcAddress(hModule,"GetAltTabInfoA"));
  this->GetAltTabInfoW = reinterpret_cast<decltype(::GetAltTabInfoW) *>(GetProcAddress(hModule,"GetAltTabInfoW"));
  this->GetListBoxInfo = reinterpret_cast<decltype(::GetListBoxInfo) *>(GetProcAddress(hModule,"GetListBoxInfo"));
  this->LockWorkStation = reinterpret_cast<decltype(::LockWorkStation) *>(GetProcAddress(hModule,"LockWorkStation"));
  this->UserHandleGrantAccess = reinterpret_cast<decltype(::UserHandleGrantAccess) *>(GetProcAddress(hModule,"UserHandleGrantAccess"));
  this->GetRawInputData = reinterpret_cast<decltype(::GetRawInputData) *>(GetProcAddress(hModule,"GetRawInputData"));
  this->GetRawInputDeviceInfoA = reinterpret_cast<decltype(::GetRawInputDeviceInfoA) *>(GetProcAddress(hModule,"GetRawInputDeviceInfoA"));
  this->GetRawInputDeviceInfoW = reinterpret_cast<decltype(::GetRawInputDeviceInfoW) *>(GetProcAddress(hModule,"GetRawInputDeviceInfoW"));
  this->GetRawInputBuffer = reinterpret_cast<decltype(::GetRawInputBuffer) *>(GetProcAddress(hModule,"GetRawInputBuffer"));
  this->RegisterRawInputDevices = reinterpret_cast<decltype(::RegisterRawInputDevices) *>(GetProcAddress(hModule,"RegisterRawInputDevices"));
  this->GetRegisteredRawInputDevices = reinterpret_cast<decltype(::GetRegisteredRawInputDevices) *>(GetProcAddress(hModule,"GetRegisteredRawInputDevices"));
  this->GetRawInputDeviceList = reinterpret_cast<decltype(::GetRawInputDeviceList) *>(GetProcAddress(hModule,"GetRawInputDeviceList"));
  this->DefRawInputProc = reinterpret_cast<decltype(::DefRawInputProc) *>(GetProcAddress(hModule,"DefRawInputProc"));
  this->GetPointerDevices = reinterpret_cast<decltype(::GetPointerDevices) *>(GetProcAddress(hModule,"GetPointerDevices"));
  this->GetPointerDevice = reinterpret_cast<decltype(::GetPointerDevice) *>(GetProcAddress(hModule,"GetPointerDevice"));
  this->GetPointerDeviceProperties = reinterpret_cast<decltype(::GetPointerDeviceProperties) *>(GetProcAddress(hModule,"GetPointerDeviceProperties"));
  this->RegisterPointerDeviceNotifications = reinterpret_cast<decltype(::RegisterPointerDeviceNotifications) *>(GetProcAddress(hModule,"RegisterPointerDeviceNotifications"));
  this->GetPointerDeviceRects = reinterpret_cast<decltype(::GetPointerDeviceRects) *>(GetProcAddress(hModule,"GetPointerDeviceRects"));
  this->GetPointerDeviceCursors = reinterpret_cast<decltype(::GetPointerDeviceCursors) *>(GetProcAddress(hModule,"GetPointerDeviceCursors"));
  this->GetRawPointerDeviceData = reinterpret_cast<decltype(::GetRawPointerDeviceData) *>(GetProcAddress(hModule,"GetRawPointerDeviceData"));
  this->ChangeWindowMessageFilter = reinterpret_cast<decltype(::ChangeWindowMessageFilter) *>(GetProcAddress(hModule,"ChangeWindowMessageFilter"));
  this->ChangeWindowMessageFilterEx = reinterpret_cast<decltype(::ChangeWindowMessageFilterEx) *>(GetProcAddress(hModule,"ChangeWindowMessageFilterEx"));
  this->GetGestureInfo = reinterpret_cast<decltype(::GetGestureInfo) *>(GetProcAddress(hModule,"GetGestureInfo"));
  this->GetGestureExtraArgs = reinterpret_cast<decltype(::GetGestureExtraArgs) *>(GetProcAddress(hModule,"GetGestureExtraArgs"));
  this->CloseGestureInfoHandle = reinterpret_cast<decltype(::CloseGestureInfoHandle) *>(GetProcAddress(hModule,"CloseGestureInfoHandle"));
  this->SetGestureConfig = reinterpret_cast<decltype(::SetGestureConfig) *>(GetProcAddress(hModule,"SetGestureConfig"));
  this->GetGestureConfig = reinterpret_cast<decltype(::GetGestureConfig) *>(GetProcAddress(hModule,"GetGestureConfig"));
  this->ShutdownBlockReasonCreate = reinterpret_cast<decltype(::ShutdownBlockReasonCreate) *>(GetProcAddress(hModule,"ShutdownBlockReasonCreate"));
  this->ShutdownBlockReasonQuery = reinterpret_cast<decltype(::ShutdownBlockReasonQuery) *>(GetProcAddress(hModule,"ShutdownBlockReasonQuery"));
  this->ShutdownBlockReasonDestroy = reinterpret_cast<decltype(::ShutdownBlockReasonDestroy) *>(GetProcAddress(hModule,"ShutdownBlockReasonDestroy"));
  this->GetCurrentInputMessageSource = reinterpret_cast<decltype(::GetCurrentInputMessageSource) *>(GetProcAddress(hModule,"GetCurrentInputMessageSource"));
  this->GetCIMSSM = reinterpret_cast<decltype(::GetCIMSSM) *>(GetProcAddress(hModule,"GetCIMSSM"));
  this->GetAutoRotationState = reinterpret_cast<decltype(::GetAutoRotationState) *>(GetProcAddress(hModule,"GetAutoRotationState"));
  this->GetDisplayAutoRotationPreferences = reinterpret_cast<decltype(::GetDisplayAutoRotationPreferences) *>(GetProcAddress(hModule,"GetDisplayAutoRotationPreferences"));
  this->GetDisplayAutoRotationPreferencesByProcessId = reinterpret_cast<decltype(::GetDisplayAutoRotationPreferencesByProcessId) *>(GetProcAddress(hModule,"GetDisplayAutoRotationPreferencesByProcessId"));
  this->SetDisplayAutoRotationPreferences = reinterpret_cast<decltype(::SetDisplayAutoRotationPreferences) *>(GetProcAddress(hModule,"SetDisplayAutoRotationPreferences"));
  this->IsImmersiveProcess = reinterpret_cast<decltype(::IsImmersiveProcess) *>(GetProcAddress(hModule,"IsImmersiveProcess"));
  this->SetProcessRestrictionExemption = reinterpret_cast<decltype(::SetProcessRestrictionExemption) *>(GetProcAddress(hModule,"SetProcessRestrictionExemption"));
  this->GetPointerInputTransform = reinterpret_cast<decltype(::GetPointerInputTransform) *>(GetProcAddress(hModule,"GetPointerInputTransform"));
  this->IsMousePointerEnabled = reinterpret_cast<decltype(::IsMousePointerEnabled) *>(GetProcAddress(hModule,"IsMousePointerEnabled"));
}


struct Imports
{
  User32 user32;
  void init();
} g_imports;


void Imports::init()
{
  LPCSTR szDllName = "user32.dll";
  CHAR szPath[MAX_PATH];
  if (!GetSystemDirectory(szPath, sizeof(szPath)))
    throw std::runtime_error("Failed to get system directory path");
  strcat(szPath, "\\");
  strcat(szPath, szDllName);
  HMODULE hModule = LoadLibrary(szPath);
  if (!hModule)
  {
    CHAR szMsg[MAX_PATH+100];
    snprintf(szMsg, sizeof(szMsg), "Failed to load %s", szPath);
    throw std::runtime_error(szMsg);
  }
  this->user32.init(hModule);
}


void init_log()
{
  auto formatter = [](logging::LogMessage const & lm)
  {
    static char const fmt[] = "%H:%M:%S";
    size_t const n = 128;
    char timeCstr[n] = {0};
    auto time = std::localtime(&lm.time);
    std::strftime(timeCstr, n, fmt, time);
    return stream_to_str("(", lm.source, ") <", timeCstr, "> [", lm.level, "] ", lm.msg);
  };
  auto const logPath = "user32.log";
  auto spLogFileSteam = std::make_shared<std::fstream>(logPath, std::ios::out|std::ios::trunc);
  auto streamHolder = [spLogFileSteam]() -> std::fstream& { return *spLogFileSteam; };
  auto spLogPrinter = std::make_shared<logging::StreamLogPrinter>(formatter, streamHolder);
  logging::root_logger().add_printer(spLogPrinter);
  logging::root_logger().set_level(logging::LogLevel::info);
  logging::log("init", logging::LogLevel::info, "Logging initialized");
}


BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason,LPVOID v)
try {
  if (reason == DLL_PROCESS_ATTACH)
  {
    init_log();
    g_imports.init();
    logging::log("init", logging::LogLevel::info, "Dll attached");
  }

  if (reason == DLL_PROCESS_DETACH)
  {
    logging::log("init", logging::LogLevel::info, "Dll detached");
  }

  return TRUE;
} catch (std::exception const & e)
{
  return FALSE;
}


DLLEXPORT int WINAPI wvsprintfA (LPSTR arg0, LPCSTR arg1, va_list arglist)
{
  return g_imports.user32.wvsprintfA(arg0, arg1, arglist);
}

DLLEXPORT int WINAPI wvsprintfW (LPWSTR arg0, LPCWSTR arg1, va_list arglist)
{
  return g_imports.user32.wvsprintfW(arg0, arg1, arglist);
}

DLLEXPORT int WINAPIV wsprintfA (LPSTR arg0, LPCSTR arg1, ...)
{
  va_list arglist;
  va_start(arglist, arg1);
  auto r = g_imports.user32.wvsprintfA(arg0, arg1, arglist);
  va_end(arglist);
  return r;
}

DLLEXPORT int WINAPIV wsprintfW (LPWSTR arg0, LPCWSTR arg1, ...)
{
  va_list arglist;
  va_start(arglist, arg1);
  auto r = g_imports.user32.wvsprintfW(arg0, arg1, arglist);
  va_end(arglist);
  return r;
}

DLLEXPORT HKL WINAPI LoadKeyboardLayoutA (LPCSTR pwszKLID, UINT Flags)
{
  return g_imports.user32.LoadKeyboardLayoutA(pwszKLID, Flags);
}

DLLEXPORT HKL WINAPI LoadKeyboardLayoutW (LPCWSTR pwszKLID, UINT Flags)
{
  return g_imports.user32.LoadKeyboardLayoutW(pwszKLID, Flags);
}

DLLEXPORT HKL WINAPI ActivateKeyboardLayout (HKL hkl, UINT Flags)
{
  return g_imports.user32.ActivateKeyboardLayout(hkl, Flags);
}

DLLEXPORT int WINAPI ToUnicodeEx (UINT wVirtKey, UINT wScanCode, CONST BYTE * lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags, HKL dwhkl)
{
  return g_imports.user32.ToUnicodeEx(wVirtKey, wScanCode, lpKeyState, pwszBuff, cchBuff, wFlags, dwhkl);
}

DLLEXPORT WINBOOL WINAPI UnloadKeyboardLayout (HKL hkl)
{
  return g_imports.user32.UnloadKeyboardLayout(hkl);
}

DLLEXPORT WINBOOL WINAPI GetKeyboardLayoutNameA (LPSTR pwszKLID)
{
  return g_imports.user32.GetKeyboardLayoutNameA(pwszKLID);
}

DLLEXPORT WINBOOL WINAPI GetKeyboardLayoutNameW (LPWSTR pwszKLID)
{
  return g_imports.user32.GetKeyboardLayoutNameW(pwszKLID);
}

DLLEXPORT int WINAPI GetKeyboardLayoutList (int nBuff, HKL * lpList)
{
  return g_imports.user32.GetKeyboardLayoutList(nBuff, lpList);
}

DLLEXPORT HKL WINAPI GetKeyboardLayout (DWORD idThread)
{
  return g_imports.user32.GetKeyboardLayout(idThread);
}

DLLEXPORT int WINAPI GetMouseMovePointsEx (UINT cbSize, LPMOUSEMOVEPOINT lppt, LPMOUSEMOVEPOINT lpptBuf, int nBufPoints, DWORD resolution)
{
  return g_imports.user32.GetMouseMovePointsEx(cbSize, lppt, lpptBuf, nBufPoints, resolution);
}

DLLEXPORT HDESK WINAPI CreateDesktopA (LPCSTR lpszDesktop, LPCSTR lpszDevice, LPDEVMODEA pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
{
  return g_imports.user32.CreateDesktopA(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa);
}

DLLEXPORT HDESK WINAPI CreateDesktopW (LPCWSTR lpszDesktop, LPCWSTR lpszDevice, LPDEVMODEW pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
{
  return g_imports.user32.CreateDesktopW(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa);
}

DLLEXPORT HDESK WINAPI CreateDesktopExA (LPCSTR lpszDesktop, LPCSTR lpszDevice, DEVMODEA * pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa, ULONG ulHeapSize, PVOID pvoid)
{
  return g_imports.user32.CreateDesktopExA(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa, ulHeapSize, pvoid);
}

DLLEXPORT HDESK WINAPI CreateDesktopExW (LPCWSTR lpszDesktop, LPCWSTR lpszDevice, DEVMODEW * pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa, ULONG ulHeapSize, PVOID pvoid)
{
  return g_imports.user32.CreateDesktopExW(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa, ulHeapSize, pvoid);
}

DLLEXPORT HDESK WINAPI OpenDesktopA (LPCSTR lpszDesktop, DWORD dwFlags, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  return g_imports.user32.OpenDesktopA(lpszDesktop, dwFlags, fInherit, dwDesiredAccess);
}

DLLEXPORT HDESK WINAPI OpenDesktopW (LPCWSTR lpszDesktop, DWORD dwFlags, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  return g_imports.user32.OpenDesktopW(lpszDesktop, dwFlags, fInherit, dwDesiredAccess);
}

DLLEXPORT HDESK WINAPI OpenInputDesktop (DWORD dwFlags, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  return g_imports.user32.OpenInputDesktop(dwFlags, fInherit, dwDesiredAccess);
}

DLLEXPORT WINBOOL WINAPI EnumDesktopsA (HWINSTA hwinsta, DESKTOPENUMPROCA lpEnumFunc, LPARAM lParam)
{
  return g_imports.user32.EnumDesktopsA(hwinsta, lpEnumFunc, lParam);
}

DLLEXPORT WINBOOL WINAPI EnumDesktopsW (HWINSTA hwinsta, DESKTOPENUMPROCW lpEnumFunc, LPARAM lParam)
{
  return g_imports.user32.EnumDesktopsW(hwinsta, lpEnumFunc, lParam);
}

DLLEXPORT WINBOOL WINAPI EnumDesktopWindows (HDESK hDesktop, WNDENUMPROC lpfn, LPARAM lParam)
{
  return g_imports.user32.EnumDesktopWindows(hDesktop, lpfn, lParam);
}

DLLEXPORT WINBOOL WINAPI SwitchDesktop (HDESK hDesktop)
{
  return g_imports.user32.SwitchDesktop(hDesktop);
}

DLLEXPORT WINBOOL WINAPI SetThreadDesktop (HDESK hDesktop)
{
  return g_imports.user32.SetThreadDesktop(hDesktop);
}

DLLEXPORT WINBOOL WINAPI CloseDesktop (HDESK hDesktop)
{
  return g_imports.user32.CloseDesktop(hDesktop);
}

DLLEXPORT HDESK WINAPI GetThreadDesktop (DWORD dwThreadId)
{
  return g_imports.user32.GetThreadDesktop(dwThreadId);
}

DLLEXPORT HWINSTA WINAPI CreateWindowStationA (LPCSTR lpwinsta, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
{
  return g_imports.user32.CreateWindowStationA(lpwinsta, dwFlags, dwDesiredAccess, lpsa);
}

DLLEXPORT HWINSTA WINAPI CreateWindowStationW (LPCWSTR lpwinsta, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
{
  return g_imports.user32.CreateWindowStationW(lpwinsta, dwFlags, dwDesiredAccess, lpsa);
}

DLLEXPORT HWINSTA WINAPI OpenWindowStationA (LPCSTR lpszWinSta, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  return g_imports.user32.OpenWindowStationA(lpszWinSta, fInherit, dwDesiredAccess);
}

DLLEXPORT HWINSTA WINAPI OpenWindowStationW (LPCWSTR lpszWinSta, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  return g_imports.user32.OpenWindowStationW(lpszWinSta, fInherit, dwDesiredAccess);
}

DLLEXPORT WINBOOL WINAPI EnumWindowStationsA (WINSTAENUMPROCA lpEnumFunc, LPARAM lParam)
{
  return g_imports.user32.EnumWindowStationsA(lpEnumFunc, lParam);
}

DLLEXPORT WINBOOL WINAPI EnumWindowStationsW (WINSTAENUMPROCW lpEnumFunc, LPARAM lParam)
{
  return g_imports.user32.EnumWindowStationsW(lpEnumFunc, lParam);
}

DLLEXPORT WINBOOL WINAPI CloseWindowStation (HWINSTA hWinSta)
{
  return g_imports.user32.CloseWindowStation(hWinSta);
}

DLLEXPORT WINBOOL WINAPI SetProcessWindowStation (HWINSTA hWinSta)
{
  return g_imports.user32.SetProcessWindowStation(hWinSta);
}

DLLEXPORT HWINSTA WINAPI GetProcessWindowStation (VOID)
{
  return g_imports.user32.GetProcessWindowStation();
}

DLLEXPORT WINBOOL WINAPI SetUserObjectSecurity (HANDLE hObj, PSECURITY_INFORMATION pSIRequested, PSECURITY_DESCRIPTOR pSID)
{
  return g_imports.user32.SetUserObjectSecurity(hObj, pSIRequested, pSID);
}

DLLEXPORT WINBOOL WINAPI GetUserObjectSecurity (HANDLE hObj, PSECURITY_INFORMATION pSIRequested, PSECURITY_DESCRIPTOR pSID, DWORD nLength, LPDWORD lpnLengthNeeded)
{
  return g_imports.user32.GetUserObjectSecurity(hObj, pSIRequested, pSID, nLength, lpnLengthNeeded);
}

DLLEXPORT WINBOOL WINAPI GetUserObjectInformationA (HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength, LPDWORD lpnLengthNeeded)
{
  return g_imports.user32.GetUserObjectInformationA(hObj, nIndex, pvInfo, nLength, lpnLengthNeeded);
}

DLLEXPORT WINBOOL WINAPI GetUserObjectInformationW (HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength, LPDWORD lpnLengthNeeded)
{
  return g_imports.user32.GetUserObjectInformationW(hObj, nIndex, pvInfo, nLength, lpnLengthNeeded);
}

DLLEXPORT WINBOOL WINAPI SetUserObjectInformationA (HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength)
{
  return g_imports.user32.SetUserObjectInformationA(hObj, nIndex, pvInfo, nLength);
}

DLLEXPORT WINBOOL WINAPI SetUserObjectInformationW (HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength)
{
  return g_imports.user32.SetUserObjectInformationW(hObj, nIndex, pvInfo, nLength);
}

DLLEXPORT WINBOOL WINAPI IsHungAppWindow (HWND hwnd)
{
  return g_imports.user32.IsHungAppWindow(hwnd);
}

DLLEXPORT VOID WINAPI DisableProcessWindowsGhosting (VOID)
{
  g_imports.user32.DisableProcessWindowsGhosting();
}

DLLEXPORT UINT WINAPI RegisterWindowMessageA (LPCSTR lpString)
{
  return g_imports.user32.RegisterWindowMessageA(lpString);
}

DLLEXPORT UINT WINAPI RegisterWindowMessageW (LPCWSTR lpString)
{
  return g_imports.user32.RegisterWindowMessageW(lpString);
}

DLLEXPORT WINBOOL WINAPI TrackMouseEvent (LPTRACKMOUSEEVENT lpEventTrack)
{
  return g_imports.user32.TrackMouseEvent(lpEventTrack);
}

DLLEXPORT WINBOOL WINAPI DrawEdge (HDC hdc, LPRECT qrc, UINT edge, UINT grfFlags)
{
  return g_imports.user32.DrawEdge(hdc, qrc, edge, grfFlags);
}

DLLEXPORT WINBOOL WINAPI DrawFrameControl (HDC arg0, LPRECT arg1, UINT arg2, UINT arg3)
{
  return g_imports.user32.DrawFrameControl(arg0, arg1, arg2, arg3);
}

DLLEXPORT WINBOOL WINAPI DrawCaption (HWND hwnd, HDC hdc, CONST RECT * lprect, UINT flags)
{
  return g_imports.user32.DrawCaption(hwnd, hdc, lprect, flags);
}

DLLEXPORT WINBOOL WINAPI DrawAnimatedRects (HWND hwnd, int idAni, CONST RECT * lprcFrom, CONST RECT * lprcTo)
{
  return g_imports.user32.DrawAnimatedRects(hwnd, idAni, lprcFrom, lprcTo);
}

DLLEXPORT WINBOOL WINAPI GetMessageA (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
  return g_imports.user32.GetMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}

DLLEXPORT WINBOOL WINAPI GetMessageW (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
  return g_imports.user32.GetMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}

DLLEXPORT WINBOOL WINAPI TranslateMessage (CONST MSG * lpMsg)
{
  return g_imports.user32.TranslateMessage(lpMsg);
}

DLLEXPORT LRESULT WINAPI DispatchMessageA (CONST MSG * lpMsg)
{
  return g_imports.user32.DispatchMessageA(lpMsg);
}

DLLEXPORT LRESULT WINAPI DispatchMessageW (CONST MSG * lpMsg)
{
  return g_imports.user32.DispatchMessageW(lpMsg);
}

DLLEXPORT WINBOOL WINAPI SetMessageQueue (int cMessagesMax)
{
  return g_imports.user32.SetMessageQueue(cMessagesMax);
}

DLLEXPORT WINBOOL WINAPI PeekMessageA (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
  return g_imports.user32.PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

DLLEXPORT WINBOOL WINAPI PeekMessageW (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
  return g_imports.user32.PeekMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

DLLEXPORT WINBOOL WINAPI RegisterHotKey (HWND hWnd, int id, UINT fsModifiers, UINT vk)
{
  return g_imports.user32.RegisterHotKey(hWnd, id, fsModifiers, vk);
}

DLLEXPORT WINBOOL WINAPI UnregisterHotKey (HWND hWnd, int id)
{
  return g_imports.user32.UnregisterHotKey(hWnd, id);
}

DLLEXPORT WINBOOL WINAPI ExitWindowsEx (UINT uFlags, DWORD dwReason)
{
  return g_imports.user32.ExitWindowsEx(uFlags, dwReason);
}

DLLEXPORT WINBOOL WINAPI SwapMouseButton (WINBOOL fSwap)
{
  return g_imports.user32.SwapMouseButton(fSwap);
}

DLLEXPORT DWORD WINAPI GetMessagePos (VOID)
{
  return g_imports.user32.GetMessagePos();
}

DLLEXPORT LONG WINAPI GetMessageTime (VOID)
{
  return g_imports.user32.GetMessageTime();
}

DLLEXPORT LPARAM WINAPI GetMessageExtraInfo (VOID)
{
  return g_imports.user32.GetMessageExtraInfo();
}

DLLEXPORT DWORD WINAPI GetUnpredictedMessagePos (VOID)
{
  return g_imports.user32.GetUnpredictedMessagePos();
}

DLLEXPORT WINBOOL WINAPI IsWow64Message (VOID)
{
  return g_imports.user32.IsWow64Message();
}

DLLEXPORT LPARAM WINAPI SetMessageExtraInfo (LPARAM lParam)
{
  return g_imports.user32.SetMessageExtraInfo(lParam);
}

DLLEXPORT LRESULT WINAPI SendMessageA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.SendMessageA(hWnd, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI SendMessageW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.SendMessageW(hWnd, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI SendMessageTimeoutA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult)
{
  return g_imports.user32.SendMessageTimeoutA(hWnd, Msg, wParam, lParam, fuFlags, uTimeout, lpdwResult);
}

DLLEXPORT LRESULT WINAPI SendMessageTimeoutW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult)
{
  return g_imports.user32.SendMessageTimeoutW(hWnd, Msg, wParam, lParam, fuFlags, uTimeout, lpdwResult);
}

DLLEXPORT WINBOOL WINAPI SendNotifyMessageA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.SendNotifyMessageA(hWnd, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI SendNotifyMessageW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.SendNotifyMessageW(hWnd, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI SendMessageCallbackA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, SENDASYNCPROC lpResultCallBack, ULONG_PTR dwData)
{
  return g_imports.user32.SendMessageCallbackA(hWnd, Msg, wParam, lParam, lpResultCallBack, dwData);
}

DLLEXPORT WINBOOL WINAPI SendMessageCallbackW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, SENDASYNCPROC lpResultCallBack, ULONG_PTR dwData)
{
  return g_imports.user32.SendMessageCallbackW(hWnd, Msg, wParam, lParam, lpResultCallBack, dwData);
}

DLLEXPORT __LONG32 WINAPI BroadcastSystemMessageExA (DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam, PBSMINFO pbsmInfo)
{
  return g_imports.user32.BroadcastSystemMessageExA(flags, lpInfo, Msg, wParam, lParam, pbsmInfo);
}

DLLEXPORT __LONG32 WINAPI BroadcastSystemMessageExW (DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam, PBSMINFO pbsmInfo)
{
  return g_imports.user32.BroadcastSystemMessageExW(flags, lpInfo, Msg, wParam, lParam, pbsmInfo);
}

DLLEXPORT __LONG32 WINAPI BroadcastSystemMessageA (DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.BroadcastSystemMessageA(flags, lpInfo, Msg, wParam, lParam);
}

DLLEXPORT __LONG32 WINAPI BroadcastSystemMessageW (DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.BroadcastSystemMessageW(flags, lpInfo, Msg, wParam, lParam);
}

DLLEXPORT HPOWERNOTIFY WINAPI RegisterPowerSettingNotification (HANDLE hRecipient, LPCGUID PowerSettingGuid, DWORD Flags)
{
  return g_imports.user32.RegisterPowerSettingNotification(hRecipient, PowerSettingGuid, Flags);
}

DLLEXPORT WINBOOL WINAPI UnregisterPowerSettingNotification (HPOWERNOTIFY Handle)
{
  return g_imports.user32.UnregisterPowerSettingNotification(Handle);
}

DLLEXPORT HPOWERNOTIFY WINAPI RegisterSuspendResumeNotification (HANDLE hRecipient, DWORD Flags)
{
  return g_imports.user32.RegisterSuspendResumeNotification(hRecipient, Flags);
}

DLLEXPORT WINBOOL WINAPI UnregisterSuspendResumeNotification (HPOWERNOTIFY Handle)
{
  return g_imports.user32.UnregisterSuspendResumeNotification(Handle);
}

DLLEXPORT WINBOOL WINAPI PostMessageA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.PostMessageA(hWnd, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI PostMessageW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.PostMessageW(hWnd, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI PostThreadMessageA (DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.PostThreadMessageA(idThread, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI PostThreadMessageW (DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.PostThreadMessageW(idThread, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI AttachThreadInput (DWORD idAttach, DWORD idAttachTo, WINBOOL fAttach)
{
  return g_imports.user32.AttachThreadInput(idAttach, idAttachTo, fAttach);
}

DLLEXPORT WINBOOL WINAPI ReplyMessage (LRESULT lResult)
{
  return g_imports.user32.ReplyMessage(lResult);
}

DLLEXPORT WINBOOL WINAPI WaitMessage (VOID)
{
  return g_imports.user32.WaitMessage();
}

DLLEXPORT DWORD WINAPI WaitForInputIdle (HANDLE hProcess, DWORD dwMilliseconds)
{
  return g_imports.user32.WaitForInputIdle(hProcess, dwMilliseconds);
}

DLLEXPORT LRESULT WINAPI DefWindowProcA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.DefWindowProcA(hWnd, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI DefWindowProcW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.DefWindowProcW(hWnd, Msg, wParam, lParam);
}

DLLEXPORT VOID WINAPI PostQuitMessage (int nExitCode)
{
  g_imports.user32.PostQuitMessage(nExitCode);
}

DLLEXPORT WINBOOL WINAPI InSendMessage (VOID)
{
  return g_imports.user32.InSendMessage();
}

DLLEXPORT DWORD WINAPI InSendMessageEx (LPVOID lpReserved)
{
  return g_imports.user32.InSendMessageEx(lpReserved);
}

DLLEXPORT UINT WINAPI GetDoubleClickTime (VOID)
{
  return g_imports.user32.GetDoubleClickTime();
}

DLLEXPORT WINBOOL WINAPI SetDoubleClickTime (UINT arg0)
{
  return g_imports.user32.SetDoubleClickTime(arg0);
}

DLLEXPORT ATOM WINAPI RegisterClassA (CONST WNDCLASSA * lpWndClass)
{
  return g_imports.user32.RegisterClassA(lpWndClass);
}

DLLEXPORT ATOM WINAPI RegisterClassW (CONST WNDCLASSW * lpWndClass)
{
  return g_imports.user32.RegisterClassW(lpWndClass);
}

DLLEXPORT WINBOOL WINAPI UnregisterClassA (LPCSTR lpClassName, HINSTANCE hInstance)
{
  return g_imports.user32.UnregisterClassA(lpClassName, hInstance);
}

DLLEXPORT WINBOOL WINAPI UnregisterClassW (LPCWSTR lpClassName, HINSTANCE hInstance)
{
  return g_imports.user32.UnregisterClassW(lpClassName, hInstance);
}

DLLEXPORT WINBOOL WINAPI GetClassInfoA (HINSTANCE hInstance, LPCSTR lpClassName, LPWNDCLASSA lpWndClass)
{
  return g_imports.user32.GetClassInfoA(hInstance, lpClassName, lpWndClass);
}

DLLEXPORT WINBOOL WINAPI GetClassInfoW (HINSTANCE hInstance, LPCWSTR lpClassName, LPWNDCLASSW lpWndClass)
{
  return g_imports.user32.GetClassInfoW(hInstance, lpClassName, lpWndClass);
}

DLLEXPORT ATOM WINAPI RegisterClassExA (CONST WNDCLASSEXA * arg0)
{
  return g_imports.user32.RegisterClassExA(arg0);
}

DLLEXPORT ATOM WINAPI RegisterClassExW (CONST WNDCLASSEXW * arg0)
{
  return g_imports.user32.RegisterClassExW(arg0);
}

DLLEXPORT WINBOOL WINAPI GetClassInfoExA (HINSTANCE hInstance, LPCSTR lpszClass, LPWNDCLASSEXA lpwcx)
{
  return g_imports.user32.GetClassInfoExA(hInstance, lpszClass, lpwcx);
}

DLLEXPORT WINBOOL WINAPI GetClassInfoExW (HINSTANCE hInstance, LPCWSTR lpszClass, LPWNDCLASSEXW lpwcx)
{
  return g_imports.user32.GetClassInfoExW(hInstance, lpszClass, lpwcx);
}

#ifdef STRICT
DLLEXPORT LRESULT WINAPI CallWindowProcA (WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.CallWindowProcA(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI CallWindowProcW (WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.CallWindowProcW(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

#else

DLLEXPORT LRESULT WINAPI CallWindowProcA (FARPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.CallWindowProcA(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI CallWindowProcW (FARPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.CallWindowProcW(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}
#endif

DLLEXPORT HDEVNOTIFY WINAPI RegisterDeviceNotificationA (HANDLE hRecipient, LPVOID NotificationFilter, DWORD Flags)
{
  return g_imports.user32.RegisterDeviceNotificationA(hRecipient, NotificationFilter, Flags);
}

DLLEXPORT HDEVNOTIFY WINAPI RegisterDeviceNotificationW (HANDLE hRecipient, LPVOID NotificationFilter, DWORD Flags)
{
  return g_imports.user32.RegisterDeviceNotificationW(hRecipient, NotificationFilter, Flags);
}

DLLEXPORT WINBOOL WINAPI UnregisterDeviceNotification (HDEVNOTIFY Handle)
{
  return g_imports.user32.UnregisterDeviceNotification(Handle);
}

DLLEXPORT HWND WINAPI CreateWindowExA (DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
  return g_imports.user32.CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

DLLEXPORT HWND WINAPI CreateWindowExW (DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
  return g_imports.user32.CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

DLLEXPORT WINBOOL WINAPI IsWindow (HWND hWnd)
{
  return g_imports.user32.IsWindow(hWnd);
}

DLLEXPORT WINBOOL WINAPI IsMenu (HMENU hMenu)
{
  return g_imports.user32.IsMenu(hMenu);
}

DLLEXPORT WINBOOL WINAPI IsChild (HWND hWndParent, HWND hWnd)
{
  return g_imports.user32.IsChild(hWndParent, hWnd);
}

DLLEXPORT WINBOOL WINAPI DestroyWindow (HWND hWnd)
{
  return g_imports.user32.DestroyWindow(hWnd);
}

DLLEXPORT WINBOOL WINAPI ShowWindow (HWND hWnd, int nCmdShow)
{
  return g_imports.user32.ShowWindow(hWnd, nCmdShow);
}

DLLEXPORT WINBOOL WINAPI AnimateWindow (HWND hWnd, DWORD dwTime, DWORD dwFlags)
{
  return g_imports.user32.AnimateWindow(hWnd, dwTime, dwFlags);
}

DLLEXPORT WINBOOL WINAPI UpdateLayeredWindow (HWND hWnd, HDC hdcDst, POINT * pptDst, SIZE * psize, HDC hdcSrc, POINT * pptSrc, COLORREF crKey, BLENDFUNCTION * pblend, DWORD dwFlags)
{
  return g_imports.user32.UpdateLayeredWindow(hWnd, hdcDst, pptDst, psize, hdcSrc, pptSrc, crKey, pblend, dwFlags);
}

DLLEXPORT WINBOOL WINAPI UpdateLayeredWindowIndirect (HWND hWnd, const UPDATELAYEREDWINDOWINFO * pULWInfo)
{
  return g_imports.user32.UpdateLayeredWindowIndirect(hWnd, pULWInfo);
}

DLLEXPORT WINBOOL WINAPI GetLayeredWindowAttributes (HWND hwnd, COLORREF * pcrKey, BYTE * pbAlpha, DWORD * pdwFlags)
{
  return g_imports.user32.GetLayeredWindowAttributes(hwnd, pcrKey, pbAlpha, pdwFlags);
}

DLLEXPORT WINBOOL WINAPI PrintWindow (HWND hwnd, HDC hdcBlt, UINT nFlags)
{
  return g_imports.user32.PrintWindow(hwnd, hdcBlt, nFlags);
}

DLLEXPORT WINBOOL WINAPI SetLayeredWindowAttributes (HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
{
  return g_imports.user32.SetLayeredWindowAttributes(hwnd, crKey, bAlpha, dwFlags);
}

DLLEXPORT WINBOOL WINAPI ShowWindowAsync (HWND hWnd, int nCmdShow)
{
  return g_imports.user32.ShowWindowAsync(hWnd, nCmdShow);
}

DLLEXPORT WINBOOL WINAPI FlashWindow (HWND hWnd, WINBOOL bInvert)
{
  return g_imports.user32.FlashWindow(hWnd, bInvert);
}

DLLEXPORT WINBOOL WINAPI FlashWindowEx (PFLASHWINFO pfwi)
{
  return g_imports.user32.FlashWindowEx(pfwi);
}

DLLEXPORT WINBOOL WINAPI ShowOwnedPopups (HWND hWnd, WINBOOL fShow)
{
  return g_imports.user32.ShowOwnedPopups(hWnd, fShow);
}

DLLEXPORT WINBOOL WINAPI OpenIcon (HWND hWnd)
{
  return g_imports.user32.OpenIcon(hWnd);
}

DLLEXPORT WINBOOL WINAPI CloseWindow (HWND hWnd)
{
  return g_imports.user32.CloseWindow(hWnd);
}

DLLEXPORT WINBOOL WINAPI MoveWindow (HWND hWnd, int X, int Y, int nWidth, int nHeight, WINBOOL bRepaint)
{
  return g_imports.user32.MoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint);
}

DLLEXPORT WINBOOL WINAPI SetWindowPos (HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
{
  return g_imports.user32.SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

DLLEXPORT WINBOOL WINAPI GetWindowPlacement (HWND hWnd, WINDOWPLACEMENT * lpwndpl)
{
  return g_imports.user32.GetWindowPlacement(hWnd, lpwndpl);
}

DLLEXPORT WINBOOL WINAPI SetWindowPlacement (HWND hWnd, CONST WINDOWPLACEMENT * lpwndpl)
{
  return g_imports.user32.SetWindowPlacement(hWnd, lpwndpl);
}

DLLEXPORT WINBOOL WINAPI GetWindowDisplayAffinity (HWND hWnd, DWORD * pdwAffinity)
{
  return g_imports.user32.GetWindowDisplayAffinity(hWnd, pdwAffinity);
}

DLLEXPORT WINBOOL WINAPI SetWindowDisplayAffinity (HWND hWnd, DWORD dwAffinity)
{
  return g_imports.user32.SetWindowDisplayAffinity(hWnd, dwAffinity);
}

DLLEXPORT HDWP WINAPI BeginDeferWindowPos (int nNumWindows)
{
  return g_imports.user32.BeginDeferWindowPos(nNumWindows);
}

DLLEXPORT HDWP WINAPI DeferWindowPos (HDWP hWinPosInfo, HWND hWnd, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
  return g_imports.user32.DeferWindowPos(hWinPosInfo, hWnd, hWndInsertAfter, x, y, cx, cy, uFlags);
}

DLLEXPORT WINBOOL WINAPI EndDeferWindowPos (HDWP hWinPosInfo)
{
  return g_imports.user32.EndDeferWindowPos(hWinPosInfo);
}

DLLEXPORT WINBOOL WINAPI IsWindowVisible (HWND hWnd)
{
  return g_imports.user32.IsWindowVisible(hWnd);
}

DLLEXPORT WINBOOL WINAPI IsIconic (HWND hWnd)
{
  return g_imports.user32.IsIconic(hWnd);
}

DLLEXPORT WINBOOL WINAPI AnyPopup (VOID)
{
  return g_imports.user32.AnyPopup();
}

DLLEXPORT WINBOOL WINAPI BringWindowToTop (HWND hWnd)
{
  return g_imports.user32.BringWindowToTop(hWnd);
}

DLLEXPORT WINBOOL WINAPI IsZoomed (HWND hWnd)
{
  return g_imports.user32.IsZoomed(hWnd);
}

DLLEXPORT HWND WINAPI CreateDialogParamA (HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  return g_imports.user32.CreateDialogParamA(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT HWND WINAPI CreateDialogParamW (HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  return g_imports.user32.CreateDialogParamW(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT HWND WINAPI CreateDialogIndirectParamA (HINSTANCE hInstance, LPCDLGTEMPLATEA lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  return g_imports.user32.CreateDialogIndirectParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT HWND WINAPI CreateDialogIndirectParamW (HINSTANCE hInstance, LPCDLGTEMPLATEW lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  return g_imports.user32.CreateDialogIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT INT_PTR WINAPI DialogBoxParamA (HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  return g_imports.user32.DialogBoxParamA(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT INT_PTR WINAPI DialogBoxParamW (HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  return g_imports.user32.DialogBoxParamW(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT INT_PTR WINAPI DialogBoxIndirectParamA (HINSTANCE hInstance, LPCDLGTEMPLATEA hDialogTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  return g_imports.user32.DialogBoxIndirectParamA(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT INT_PTR WINAPI DialogBoxIndirectParamW (HINSTANCE hInstance, LPCDLGTEMPLATEW hDialogTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  return g_imports.user32.DialogBoxIndirectParamW(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT WINBOOL WINAPI EndDialog (HWND hDlg, INT_PTR nResult)
{
  return g_imports.user32.EndDialog(hDlg, nResult);
}

DLLEXPORT HWND WINAPI GetDlgItem (HWND hDlg, int nIDDlgItem)
{
  return g_imports.user32.GetDlgItem(hDlg, nIDDlgItem);
}

DLLEXPORT WINBOOL WINAPI SetDlgItemInt (HWND hDlg, int nIDDlgItem, UINT uValue, WINBOOL bSigned)
{
  return g_imports.user32.SetDlgItemInt(hDlg, nIDDlgItem, uValue, bSigned);
}

DLLEXPORT UINT WINAPI GetDlgItemInt (HWND hDlg, int nIDDlgItem, WINBOOL * lpTranslated, WINBOOL bSigned)
{
  return g_imports.user32.GetDlgItemInt(hDlg, nIDDlgItem, lpTranslated, bSigned);
}

DLLEXPORT WINBOOL WINAPI SetDlgItemTextA (HWND hDlg, int nIDDlgItem, LPCSTR lpString)
{
  return g_imports.user32.SetDlgItemTextA(hDlg, nIDDlgItem, lpString);
}

DLLEXPORT WINBOOL WINAPI SetDlgItemTextW (HWND hDlg, int nIDDlgItem, LPCWSTR lpString)
{
  return g_imports.user32.SetDlgItemTextW(hDlg, nIDDlgItem, lpString);
}

DLLEXPORT UINT WINAPI GetDlgItemTextA (HWND hDlg, int nIDDlgItem, LPSTR lpString, int cchMax)
{
  return g_imports.user32.GetDlgItemTextA(hDlg, nIDDlgItem, lpString, cchMax);
}

DLLEXPORT UINT WINAPI GetDlgItemTextW (HWND hDlg, int nIDDlgItem, LPWSTR lpString, int cchMax)
{
  return g_imports.user32.GetDlgItemTextW(hDlg, nIDDlgItem, lpString, cchMax);
}

DLLEXPORT WINBOOL WINAPI CheckDlgButton (HWND hDlg, int nIDButton, UINT uCheck)
{
  return g_imports.user32.CheckDlgButton(hDlg, nIDButton, uCheck);
}

DLLEXPORT WINBOOL WINAPI CheckRadioButton (HWND hDlg, int nIDFirstButton, int nIDLastButton, int nIDCheckButton)
{
  return g_imports.user32.CheckRadioButton(hDlg, nIDFirstButton, nIDLastButton, nIDCheckButton);
}

DLLEXPORT UINT WINAPI IsDlgButtonChecked (HWND hDlg, int nIDButton)
{
  return g_imports.user32.IsDlgButtonChecked(hDlg, nIDButton);
}

DLLEXPORT LRESULT WINAPI SendDlgItemMessageA (HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.SendDlgItemMessageA(hDlg, nIDDlgItem, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI SendDlgItemMessageW (HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.SendDlgItemMessageW(hDlg, nIDDlgItem, Msg, wParam, lParam);
}

DLLEXPORT HWND WINAPI GetNextDlgGroupItem (HWND hDlg, HWND hCtl, WINBOOL bPrevious)
{
  return g_imports.user32.GetNextDlgGroupItem(hDlg, hCtl, bPrevious);
}

DLLEXPORT HWND WINAPI GetNextDlgTabItem (HWND hDlg, HWND hCtl, WINBOOL bPrevious)
{
  return g_imports.user32.GetNextDlgTabItem(hDlg, hCtl, bPrevious);
}

DLLEXPORT int WINAPI GetDlgCtrlID (HWND hWnd)
{
  return g_imports.user32.GetDlgCtrlID(hWnd);
}

DLLEXPORT __LONG32 WINAPI GetDialogBaseUnits (VOID)
{
  return g_imports.user32.GetDialogBaseUnits();
}

DLLEXPORT LRESULT WINAPI DefDlgProcA (HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.DefDlgProcA(hDlg, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI DefDlgProcW (HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.DefDlgProcW(hDlg, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI CallMsgFilterA (LPMSG lpMsg, int nCode)
{
  return g_imports.user32.CallMsgFilterA(lpMsg, nCode);
}

DLLEXPORT WINBOOL WINAPI CallMsgFilterW (LPMSG lpMsg, int nCode)
{
  return g_imports.user32.CallMsgFilterW(lpMsg, nCode);
}

DLLEXPORT WINBOOL WINAPI OpenClipboard (HWND hWndNewOwner)
{
  return g_imports.user32.OpenClipboard(hWndNewOwner);
}

DLLEXPORT WINBOOL WINAPI CloseClipboard (VOID)
{
  return g_imports.user32.CloseClipboard();
}

DLLEXPORT DWORD WINAPI GetClipboardSequenceNumber (VOID)
{
  return g_imports.user32.GetClipboardSequenceNumber();
}

DLLEXPORT HWND WINAPI GetClipboardOwner (VOID)
{
  return g_imports.user32.GetClipboardOwner();
}

DLLEXPORT HWND WINAPI SetClipboardViewer (HWND hWndNewViewer)
{
  return g_imports.user32.SetClipboardViewer(hWndNewViewer);
}

DLLEXPORT HWND WINAPI GetClipboardViewer (VOID)
{
  return g_imports.user32.GetClipboardViewer();
}

DLLEXPORT WINBOOL WINAPI ChangeClipboardChain (HWND hWndRemove, HWND hWndNewNext)
{
  return g_imports.user32.ChangeClipboardChain(hWndRemove, hWndNewNext);
}

DLLEXPORT HANDLE WINAPI SetClipboardData (UINT uFormat, HANDLE hMem)
{
  return g_imports.user32.SetClipboardData(uFormat, hMem);
}

DLLEXPORT HANDLE WINAPI GetClipboardData (UINT uFormat)
{
  return g_imports.user32.GetClipboardData(uFormat);
}

DLLEXPORT UINT WINAPI RegisterClipboardFormatA (LPCSTR lpszFormat)
{
  return g_imports.user32.RegisterClipboardFormatA(lpszFormat);
}

DLLEXPORT UINT WINAPI RegisterClipboardFormatW (LPCWSTR lpszFormat)
{
  return g_imports.user32.RegisterClipboardFormatW(lpszFormat);
}

DLLEXPORT int WINAPI CountClipboardFormats (VOID)
{
  return g_imports.user32.CountClipboardFormats();
}

DLLEXPORT UINT WINAPI EnumClipboardFormats (UINT format)
{
  return g_imports.user32.EnumClipboardFormats(format);
}

DLLEXPORT int WINAPI GetClipboardFormatNameA (UINT format, LPSTR lpszFormatName, int cchMaxCount)
{
  return g_imports.user32.GetClipboardFormatNameA(format, lpszFormatName, cchMaxCount);
}

DLLEXPORT int WINAPI GetClipboardFormatNameW (UINT format, LPWSTR lpszFormatName, int cchMaxCount)
{
  return g_imports.user32.GetClipboardFormatNameW(format, lpszFormatName, cchMaxCount);
}

DLLEXPORT WINBOOL WINAPI EmptyClipboard (VOID)
{
  return g_imports.user32.EmptyClipboard();
}

DLLEXPORT WINBOOL WINAPI IsClipboardFormatAvailable (UINT format)
{
  return g_imports.user32.IsClipboardFormatAvailable(format);
}

DLLEXPORT int WINAPI GetPriorityClipboardFormat (UINT * paFormatPriorityList, int cFormats)
{
  return g_imports.user32.GetPriorityClipboardFormat(paFormatPriorityList, cFormats);
}

DLLEXPORT HWND WINAPI GetOpenClipboardWindow (VOID)
{
  return g_imports.user32.GetOpenClipboardWindow();
}

DLLEXPORT WINBOOL WINAPI AddClipboardFormatListener (HWND hwnd)
{
  return g_imports.user32.AddClipboardFormatListener(hwnd);
}

DLLEXPORT WINBOOL WINAPI RemoveClipboardFormatListener (HWND hwnd)
{
  return g_imports.user32.RemoveClipboardFormatListener(hwnd);
}

DLLEXPORT WINBOOL WINAPI GetUpdatedClipboardFormats (PUINT lpuiFormats, UINT cFormats, PUINT pcFormatsOut)
{
  return g_imports.user32.GetUpdatedClipboardFormats(lpuiFormats, cFormats, pcFormatsOut);
}

DLLEXPORT WINBOOL WINAPI CharToOemA (LPCSTR lpszSrc, LPSTR lpszDst)
{
  return g_imports.user32.CharToOemA(lpszSrc, lpszDst);
}

DLLEXPORT WINBOOL WINAPI CharToOemW (LPCWSTR lpszSrc, LPSTR lpszDst)
{
  return g_imports.user32.CharToOemW(lpszSrc, lpszDst);
}

DLLEXPORT WINBOOL WINAPI OemToCharA (LPCSTR lpszSrc, LPSTR lpszDst)
{
  return g_imports.user32.OemToCharA(lpszSrc, lpszDst);
}

DLLEXPORT WINBOOL WINAPI OemToCharW (LPCSTR lpszSrc, LPWSTR lpszDst)
{
  return g_imports.user32.OemToCharW(lpszSrc, lpszDst);
}

DLLEXPORT WINBOOL WINAPI CharToOemBuffA (LPCSTR lpszSrc, LPSTR lpszDst, DWORD cchDstLength)
{
  return g_imports.user32.CharToOemBuffA(lpszSrc, lpszDst, cchDstLength);
}

DLLEXPORT WINBOOL WINAPI CharToOemBuffW (LPCWSTR lpszSrc, LPSTR lpszDst, DWORD cchDstLength)
{
  return g_imports.user32.CharToOemBuffW(lpszSrc, lpszDst, cchDstLength);
}

DLLEXPORT WINBOOL WINAPI OemToCharBuffA (LPCSTR lpszSrc, LPSTR lpszDst, DWORD cchDstLength)
{
  return g_imports.user32.OemToCharBuffA(lpszSrc, lpszDst, cchDstLength);
}

DLLEXPORT WINBOOL WINAPI OemToCharBuffW (LPCSTR lpszSrc, LPWSTR lpszDst, DWORD cchDstLength)
{
  return g_imports.user32.OemToCharBuffW(lpszSrc, lpszDst, cchDstLength);
}

DLLEXPORT LPSTR WINAPI CharUpperA (LPSTR lpsz)
{
  return g_imports.user32.CharUpperA(lpsz);
}

DLLEXPORT LPWSTR WINAPI CharUpperW (LPWSTR lpsz)
{
  return g_imports.user32.CharUpperW(lpsz);
}

DLLEXPORT DWORD WINAPI CharUpperBuffA (LPSTR lpsz, DWORD cchLength)
{
  return g_imports.user32.CharUpperBuffA(lpsz, cchLength);
}

DLLEXPORT DWORD WINAPI CharUpperBuffW (LPWSTR lpsz, DWORD cchLength)
{
  return g_imports.user32.CharUpperBuffW(lpsz, cchLength);
}

DLLEXPORT LPSTR WINAPI CharLowerA (LPSTR lpsz)
{
  return g_imports.user32.CharLowerA(lpsz);
}

DLLEXPORT LPWSTR WINAPI CharLowerW (LPWSTR lpsz)
{
  return g_imports.user32.CharLowerW(lpsz);
}

DLLEXPORT DWORD WINAPI CharLowerBuffA (LPSTR lpsz, DWORD cchLength)
{
  return g_imports.user32.CharLowerBuffA(lpsz, cchLength);
}

DLLEXPORT DWORD WINAPI CharLowerBuffW (LPWSTR lpsz, DWORD cchLength)
{
  return g_imports.user32.CharLowerBuffW(lpsz, cchLength);
}

DLLEXPORT LPSTR WINAPI CharNextA (LPCSTR lpsz)
{
  return g_imports.user32.CharNextA(lpsz);
}

DLLEXPORT LPWSTR WINAPI CharNextW (LPCWSTR lpsz)
{
  return g_imports.user32.CharNextW(lpsz);
}

DLLEXPORT LPSTR WINAPI CharPrevA (LPCSTR lpszStart, LPCSTR lpszCurrent)
{
  return g_imports.user32.CharPrevA(lpszStart, lpszCurrent);
}

DLLEXPORT LPWSTR WINAPI CharPrevW (LPCWSTR lpszStart, LPCWSTR lpszCurrent)
{
  return g_imports.user32.CharPrevW(lpszStart, lpszCurrent);
}

DLLEXPORT LPSTR WINAPI CharNextExA (WORD CodePage, LPCSTR lpCurrentChar, DWORD dwFlags)
{
  return g_imports.user32.CharNextExA(CodePage, lpCurrentChar, dwFlags);
}

DLLEXPORT LPSTR WINAPI CharPrevExA (WORD CodePage, LPCSTR lpStart, LPCSTR lpCurrentChar, DWORD dwFlags)
{
  return g_imports.user32.CharPrevExA(CodePage, lpStart, lpCurrentChar, dwFlags);
}

DLLEXPORT WINBOOL WINAPI IsCharAlphaA (CHAR ch)
{
  return g_imports.user32.IsCharAlphaA(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharAlphaW (WCHAR ch)
{
  return g_imports.user32.IsCharAlphaW(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharAlphaNumericA (CHAR ch)
{
  return g_imports.user32.IsCharAlphaNumericA(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharAlphaNumericW (WCHAR ch)
{
  return g_imports.user32.IsCharAlphaNumericW(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharUpperA (CHAR ch)
{
  return g_imports.user32.IsCharUpperA(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharUpperW (WCHAR ch)
{
  return g_imports.user32.IsCharUpperW(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharLowerA (CHAR ch)
{
  return g_imports.user32.IsCharLowerA(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharLowerW (WCHAR ch)
{
  return g_imports.user32.IsCharLowerW(ch);
}

DLLEXPORT HWND WINAPI SetFocus (HWND hWnd)
{
  return g_imports.user32.SetFocus(hWnd);
}

DLLEXPORT HWND WINAPI GetActiveWindow (VOID)
{
  return g_imports.user32.GetActiveWindow();
}

DLLEXPORT HWND WINAPI GetFocus (VOID)
{
  return g_imports.user32.GetFocus();
}

DLLEXPORT UINT WINAPI GetKBCodePage (VOID)
{
  return g_imports.user32.GetKBCodePage();
}

DLLEXPORT SHORT WINAPI GetKeyState (int nVirtKey)
{
  return g_imports.user32.GetKeyState(nVirtKey);
}

DLLEXPORT SHORT WINAPI GetAsyncKeyState (int vKey)
{
  return g_imports.user32.GetAsyncKeyState(vKey);
}

DLLEXPORT WINBOOL WINAPI GetKeyboardState (PBYTE lpKeyState)
{
  return g_imports.user32.GetKeyboardState(lpKeyState);
}

DLLEXPORT WINBOOL WINAPI SetKeyboardState (LPBYTE lpKeyState)
{
  return g_imports.user32.SetKeyboardState(lpKeyState);
}

DLLEXPORT int WINAPI GetKeyNameTextA (LONG lParam, LPSTR lpString, int cchSize)
{
  return g_imports.user32.GetKeyNameTextA(lParam, lpString, cchSize);
}

DLLEXPORT int WINAPI GetKeyNameTextW (LONG lParam, LPWSTR lpString, int cchSize)
{
  return g_imports.user32.GetKeyNameTextW(lParam, lpString, cchSize);
}

DLLEXPORT int WINAPI GetKeyboardType (int nTypeFlag)
{
  return g_imports.user32.GetKeyboardType(nTypeFlag);
}

DLLEXPORT int WINAPI ToAscii (UINT uVirtKey, UINT uScanCode, CONST BYTE * lpKeyState, LPWORD lpChar, UINT uFlags)
{
  return g_imports.user32.ToAscii(uVirtKey, uScanCode, lpKeyState, lpChar, uFlags);
}

DLLEXPORT int WINAPI ToAsciiEx (UINT uVirtKey, UINT uScanCode, CONST BYTE * lpKeyState, LPWORD lpChar, UINT uFlags, HKL dwhkl)
{
  return g_imports.user32.ToAsciiEx(uVirtKey, uScanCode, lpKeyState, lpChar, uFlags, dwhkl);
}

DLLEXPORT int WINAPI ToUnicode (UINT wVirtKey, UINT wScanCode, CONST BYTE * lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags)
{
  return g_imports.user32.ToUnicode(wVirtKey, wScanCode, lpKeyState, pwszBuff, cchBuff, wFlags);
}

DLLEXPORT DWORD WINAPI OemKeyScan (WORD wOemChar)
{
  return g_imports.user32.OemKeyScan(wOemChar);
}

DLLEXPORT SHORT WINAPI VkKeyScanA (CHAR ch)
{
  return g_imports.user32.VkKeyScanA(ch);
}

DLLEXPORT SHORT WINAPI VkKeyScanW (WCHAR ch)
{
  return g_imports.user32.VkKeyScanW(ch);
}

DLLEXPORT SHORT WINAPI VkKeyScanExA (CHAR ch, HKL dwhkl)
{
  return g_imports.user32.VkKeyScanExA(ch, dwhkl);
}

DLLEXPORT SHORT WINAPI VkKeyScanExW (WCHAR ch, HKL dwhkl)
{
  return g_imports.user32.VkKeyScanExW(ch, dwhkl);
}

DLLEXPORT VOID WINAPI keybd_event (BYTE bVk, BYTE bScan, DWORD dwFlags, ULONG_PTR dwExtraInfo)
{
  g_imports.user32.keybd_event(bVk, bScan, dwFlags, dwExtraInfo);
}

DLLEXPORT VOID WINAPI mouse_event (DWORD dwFlags, DWORD dx, DWORD dy, DWORD dwData, ULONG_PTR dwExtraInfo)
{
  g_imports.user32.mouse_event(dwFlags, dx, dy, dwData, dwExtraInfo);
}

DLLEXPORT UINT WINAPI SendInput (UINT cInputs, LPINPUT pInputs, int cbSize)
{
  return g_imports.user32.SendInput(cInputs, pInputs, cbSize);
}

DLLEXPORT WINBOOL WINAPI GetTouchInputInfo (HTOUCHINPUT hTouchInput, UINT cInputs, PTOUCHINPUT pInputs, int cbSize)
{
  return g_imports.user32.GetTouchInputInfo(hTouchInput, cInputs, pInputs, cbSize);
}

DLLEXPORT WINBOOL WINAPI CloseTouchInputHandle (HTOUCHINPUT hTouchInput)
{
  return g_imports.user32.CloseTouchInputHandle(hTouchInput);
}

DLLEXPORT WINBOOL WINAPI RegisterTouchWindow (HWND hwnd, ULONG ulFlags)
{
  return g_imports.user32.RegisterTouchWindow(hwnd, ulFlags);
}

DLLEXPORT WINBOOL WINAPI UnregisterTouchWindow (HWND hwnd)
{
  return g_imports.user32.UnregisterTouchWindow(hwnd);
}

DLLEXPORT WINBOOL WINAPI IsTouchWindow (HWND hwnd, PULONG pulFlags)
{
  return g_imports.user32.IsTouchWindow(hwnd, pulFlags);
}

DLLEXPORT WINBOOL WINAPI InitializeTouchInjection (UINT32 maxCount, DWORD dwMode)
{
  return g_imports.user32.InitializeTouchInjection(maxCount, dwMode);
}

DLLEXPORT WINBOOL WINAPI InjectTouchInput (UINT32 count, CONST POINTER_TOUCH_INFO * contacts)
{
  return g_imports.user32.InjectTouchInput(count, contacts);
}

DLLEXPORT WINBOOL WINAPI GetPointerType (UINT32 pointerId, POINTER_INPUT_TYPE * pointerType)
{
  return g_imports.user32.GetPointerType(pointerId, pointerType);
}

DLLEXPORT WINBOOL WINAPI GetPointerCursorId (UINT32 pointerId, UINT32 * cursorId)
{
  return g_imports.user32.GetPointerCursorId(pointerId, cursorId);
}

DLLEXPORT WINBOOL WINAPI GetPointerInfo (UINT32 pointerId, POINTER_INFO * pointerInfo)
{
  return g_imports.user32.GetPointerInfo(pointerId, pointerInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerInfoHistory (UINT32 pointerId, UINT32 * entriesCount, POINTER_INFO * pointerInfo)
{
  return g_imports.user32.GetPointerInfoHistory(pointerId, entriesCount, pointerInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerFrameInfo (UINT32 pointerId, UINT32 * pointerCount, POINTER_INFO * pointerInfo)
{
  return g_imports.user32.GetPointerFrameInfo(pointerId, pointerCount, pointerInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerFrameInfoHistory (UINT32 pointerId, UINT32 * entriesCount, UINT32 * pointerCount, POINTER_INFO * pointerInfo)
{
  return g_imports.user32.GetPointerFrameInfoHistory(pointerId, entriesCount, pointerCount, pointerInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerTouchInfo (UINT32 pointerId, POINTER_TOUCH_INFO * touchInfo)
{
  return g_imports.user32.GetPointerTouchInfo(pointerId, touchInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerTouchInfoHistory (UINT32 pointerId, UINT32 * entriesCount, POINTER_TOUCH_INFO * touchInfo)
{
  return g_imports.user32.GetPointerTouchInfoHistory(pointerId, entriesCount, touchInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerFrameTouchInfo (UINT32 pointerId, UINT32 * pointerCount, POINTER_TOUCH_INFO * touchInfo)
{
  return g_imports.user32.GetPointerFrameTouchInfo(pointerId, pointerCount, touchInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerFrameTouchInfoHistory (UINT32 pointerId, UINT32 * entriesCount, UINT32 * pointerCount, POINTER_TOUCH_INFO * touchInfo)
{
  return g_imports.user32.GetPointerFrameTouchInfoHistory(pointerId, entriesCount, pointerCount, touchInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerPenInfo (UINT32 pointerId, POINTER_PEN_INFO * penInfo)
{
  return g_imports.user32.GetPointerPenInfo(pointerId, penInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerPenInfoHistory (UINT32 pointerId, UINT32 * entriesCount, POINTER_PEN_INFO * penInfo)
{
  return g_imports.user32.GetPointerPenInfoHistory(pointerId, entriesCount, penInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerFramePenInfo (UINT32 pointerId, UINT32 * pointerCount, POINTER_PEN_INFO * penInfo)
{
  return g_imports.user32.GetPointerFramePenInfo(pointerId, pointerCount, penInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerFramePenInfoHistory (UINT32 pointerId, UINT32 * entriesCount, UINT32 * pointerCount, POINTER_PEN_INFO * penInfo)
{
  return g_imports.user32.GetPointerFramePenInfoHistory(pointerId, entriesCount, pointerCount, penInfo);
}

DLLEXPORT WINBOOL WINAPI SkipPointerFrameMessages (UINT32 pointerId)
{
  return g_imports.user32.SkipPointerFrameMessages(pointerId);
}

DLLEXPORT WINBOOL WINAPI RegisterPointerInputTarget (HWND hwnd, POINTER_INPUT_TYPE pointerType)
{
  return g_imports.user32.RegisterPointerInputTarget(hwnd, pointerType);
}

DLLEXPORT WINBOOL WINAPI UnregisterPointerInputTarget (HWND hwnd, POINTER_INPUT_TYPE pointerType)
{
  return g_imports.user32.UnregisterPointerInputTarget(hwnd, pointerType);
}

DLLEXPORT WINBOOL WINAPI EnableMouseInPointer (WINBOOL fEnable)
{
  return g_imports.user32.EnableMouseInPointer(fEnable);
}

DLLEXPORT WINBOOL WINAPI IsMouseInPointerEnabled (VOID)
{
  return g_imports.user32.IsMouseInPointerEnabled();
}

DLLEXPORT WINBOOL WINAPI RegisterTouchHitTestingWindow (HWND hwnd, ULONG value)
{
  return g_imports.user32.RegisterTouchHitTestingWindow(hwnd, value);
}

DLLEXPORT WINBOOL WINAPI EvaluateProximityToRect (const RECT * controlBoundingBox, const TOUCH_HIT_TESTING_INPUT * pHitTestingInput, TOUCH_HIT_TESTING_PROXIMITY_EVALUATION * pProximityEval)
{
  return g_imports.user32.EvaluateProximityToRect(controlBoundingBox, pHitTestingInput, pProximityEval);
}

DLLEXPORT WINBOOL WINAPI EvaluateProximityToPolygon (UINT32 numVertices, const POINT * controlPolygon, const TOUCH_HIT_TESTING_INPUT * pHitTestingInput, TOUCH_HIT_TESTING_PROXIMITY_EVALUATION * pProximityEval)
{
  return g_imports.user32.EvaluateProximityToPolygon(numVertices, controlPolygon, pHitTestingInput, pProximityEval);
}

DLLEXPORT LRESULT WINAPI PackTouchHitTestingProximityEvaluation (const TOUCH_HIT_TESTING_INPUT * pHitTestingInput, const TOUCH_HIT_TESTING_PROXIMITY_EVALUATION * pProximityEval)
{
  return g_imports.user32.PackTouchHitTestingProximityEvaluation(pHitTestingInput, pProximityEval);
}

DLLEXPORT WINBOOL WINAPI GetWindowFeedbackSetting (HWND hwnd, FEEDBACK_TYPE feedback, DWORD dwFlags, UINT32 * pSize, VOID * config)
{
  return g_imports.user32.GetWindowFeedbackSetting(hwnd, feedback, dwFlags, pSize, config);
}

DLLEXPORT WINBOOL WINAPI SetWindowFeedbackSetting (HWND hwnd, FEEDBACK_TYPE feedback, DWORD dwFlags, UINT32 size, CONST VOID * configuration)
{
  return g_imports.user32.SetWindowFeedbackSetting(hwnd, feedback, dwFlags, size, configuration);
}

DLLEXPORT WINBOOL WINAPI GetLastInputInfo (PLASTINPUTINFO plii)
{
  return g_imports.user32.GetLastInputInfo(plii);
}

DLLEXPORT UINT WINAPI MapVirtualKeyA (UINT uCode, UINT uMapType)
{
  return g_imports.user32.MapVirtualKeyA(uCode, uMapType);
}

DLLEXPORT UINT WINAPI MapVirtualKeyW (UINT uCode, UINT uMapType)
{
  return g_imports.user32.MapVirtualKeyW(uCode, uMapType);
}

DLLEXPORT UINT WINAPI MapVirtualKeyExA (UINT uCode, UINT uMapType, HKL dwhkl)
{
  return g_imports.user32.MapVirtualKeyExA(uCode, uMapType, dwhkl);
}

DLLEXPORT UINT WINAPI MapVirtualKeyExW (UINT uCode, UINT uMapType, HKL dwhkl)
{
  return g_imports.user32.MapVirtualKeyExW(uCode, uMapType, dwhkl);
}

DLLEXPORT WINBOOL WINAPI GetInputState (VOID)
{
  return g_imports.user32.GetInputState();
}

DLLEXPORT DWORD WINAPI GetQueueStatus (UINT flags)
{
  return g_imports.user32.GetQueueStatus(flags);
}

DLLEXPORT HWND WINAPI GetCapture (VOID)
{
  return g_imports.user32.GetCapture();
}

DLLEXPORT HWND WINAPI SetCapture (HWND hWnd)
{
  return g_imports.user32.SetCapture(hWnd);
}

DLLEXPORT WINBOOL WINAPI ReleaseCapture (VOID)
{
  return g_imports.user32.ReleaseCapture();
}

DLLEXPORT DWORD WINAPI MsgWaitForMultipleObjects (DWORD nCount, CONST HANDLE * pHandles, WINBOOL fWaitAll, DWORD dwMilliseconds, DWORD dwWakeMask)
{
  return g_imports.user32.MsgWaitForMultipleObjects(nCount, pHandles, fWaitAll, dwMilliseconds, dwWakeMask);
}

DLLEXPORT DWORD WINAPI MsgWaitForMultipleObjectsEx (DWORD nCount, CONST HANDLE * pHandles, DWORD dwMilliseconds, DWORD dwWakeMask, DWORD dwFlags)
{
  return g_imports.user32.MsgWaitForMultipleObjectsEx(nCount, pHandles, dwMilliseconds, dwWakeMask, dwFlags);
}

DLLEXPORT UINT_PTR WINAPI SetTimer (HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc)
{
  return g_imports.user32.SetTimer(hWnd, nIDEvent, uElapse, lpTimerFunc);
}

DLLEXPORT WINBOOL WINAPI KillTimer (HWND hWnd, UINT_PTR uIDEvent)
{
  return g_imports.user32.KillTimer(hWnd, uIDEvent);
}

DLLEXPORT WINBOOL WINAPI IsWindowUnicode (HWND hWnd)
{
  return g_imports.user32.IsWindowUnicode(hWnd);
}

DLLEXPORT WINBOOL WINAPI EnableWindow (HWND hWnd, WINBOOL bEnable)
{
  return g_imports.user32.EnableWindow(hWnd, bEnable);
}

DLLEXPORT WINBOOL WINAPI IsWindowEnabled (HWND hWnd)
{
  return g_imports.user32.IsWindowEnabled(hWnd);
}

DLLEXPORT HACCEL WINAPI LoadAcceleratorsA (HINSTANCE hInstance, LPCSTR lpTableName)
{
  return g_imports.user32.LoadAcceleratorsA(hInstance, lpTableName);
}

DLLEXPORT HACCEL WINAPI LoadAcceleratorsW (HINSTANCE hInstance, LPCWSTR lpTableName)
{
  return g_imports.user32.LoadAcceleratorsW(hInstance, lpTableName);
}

DLLEXPORT HACCEL WINAPI CreateAcceleratorTableA (LPACCEL paccel, int cAccel)
{
  return g_imports.user32.CreateAcceleratorTableA(paccel, cAccel);
}

DLLEXPORT HACCEL WINAPI CreateAcceleratorTableW (LPACCEL paccel, int cAccel)
{
  return g_imports.user32.CreateAcceleratorTableW(paccel, cAccel);
}

DLLEXPORT WINBOOL WINAPI DestroyAcceleratorTable (HACCEL hAccel)
{
  return g_imports.user32.DestroyAcceleratorTable(hAccel);
}

DLLEXPORT int WINAPI CopyAcceleratorTableA (HACCEL hAccelSrc, LPACCEL lpAccelDst, int cAccelEntries)
{
  return g_imports.user32.CopyAcceleratorTableA(hAccelSrc, lpAccelDst, cAccelEntries);
}

DLLEXPORT int WINAPI CopyAcceleratorTableW (HACCEL hAccelSrc, LPACCEL lpAccelDst, int cAccelEntries)
{
  return g_imports.user32.CopyAcceleratorTableW(hAccelSrc, lpAccelDst, cAccelEntries);
}

DLLEXPORT int WINAPI TranslateAcceleratorA (HWND hWnd, HACCEL hAccTable, LPMSG lpMsg)
{
  return g_imports.user32.TranslateAcceleratorA(hWnd, hAccTable, lpMsg);
}

DLLEXPORT int WINAPI TranslateAcceleratorW (HWND hWnd, HACCEL hAccTable, LPMSG lpMsg)
{
  return g_imports.user32.TranslateAcceleratorW(hWnd, hAccTable, lpMsg);
}

DLLEXPORT UINT_PTR WINAPI SetCoalescableTimer (HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc, ULONG uToleranceDelay)
{
  return g_imports.user32.SetCoalescableTimer(hWnd, nIDEvent, uElapse, lpTimerFunc, uToleranceDelay);
}

DLLEXPORT int WINAPI GetSystemMetrics (int nIndex)
{
  return g_imports.user32.GetSystemMetrics(nIndex);
}

DLLEXPORT HMENU WINAPI LoadMenuA (HINSTANCE hInstance, LPCSTR lpMenuName)
{
  return g_imports.user32.LoadMenuA(hInstance, lpMenuName);
}

DLLEXPORT HMENU WINAPI LoadMenuW (HINSTANCE hInstance, LPCWSTR lpMenuName)
{
  return g_imports.user32.LoadMenuW(hInstance, lpMenuName);
}

DLLEXPORT HMENU WINAPI LoadMenuIndirectA (CONST MENUTEMPLATEA * lpMenuTemplate)
{
  return g_imports.user32.LoadMenuIndirectA(lpMenuTemplate);
}

DLLEXPORT HMENU WINAPI LoadMenuIndirectW (CONST MENUTEMPLATEW * lpMenuTemplate)
{
  return g_imports.user32.LoadMenuIndirectW(lpMenuTemplate);
}

DLLEXPORT HMENU WINAPI GetMenu (HWND hWnd)
{
  return g_imports.user32.GetMenu(hWnd);
}

DLLEXPORT WINBOOL WINAPI SetMenu (HWND hWnd, HMENU hMenu)
{
  return g_imports.user32.SetMenu(hWnd, hMenu);
}

DLLEXPORT WINBOOL WINAPI ChangeMenuA (HMENU hMenu, UINT cmd, LPCSTR lpszNewItem, UINT cmdInsert, UINT flags)
{
  return g_imports.user32.ChangeMenuA(hMenu, cmd, lpszNewItem, cmdInsert, flags);
}

DLLEXPORT WINBOOL WINAPI ChangeMenuW (HMENU hMenu, UINT cmd, LPCWSTR lpszNewItem, UINT cmdInsert, UINT flags)
{
  return g_imports.user32.ChangeMenuW(hMenu, cmd, lpszNewItem, cmdInsert, flags);
}

DLLEXPORT WINBOOL WINAPI HiliteMenuItem (HWND hWnd, HMENU hMenu, UINT uIDHiliteItem, UINT uHilite)
{
  return g_imports.user32.HiliteMenuItem(hWnd, hMenu, uIDHiliteItem, uHilite);
}

DLLEXPORT int WINAPI GetMenuStringA (HMENU hMenu, UINT uIDItem, LPSTR lpString, int cchMax, UINT flags)
{
  return g_imports.user32.GetMenuStringA(hMenu, uIDItem, lpString, cchMax, flags);
}

DLLEXPORT int WINAPI GetMenuStringW (HMENU hMenu, UINT uIDItem, LPWSTR lpString, int cchMax, UINT flags)
{
  return g_imports.user32.GetMenuStringW(hMenu, uIDItem, lpString, cchMax, flags);
}

DLLEXPORT UINT WINAPI GetMenuState (HMENU hMenu, UINT uId, UINT uFlags)
{
  return g_imports.user32.GetMenuState(hMenu, uId, uFlags);
}

DLLEXPORT WINBOOL WINAPI DrawMenuBar (HWND hWnd)
{
  return g_imports.user32.DrawMenuBar(hWnd);
}

DLLEXPORT HMENU WINAPI GetSystemMenu (HWND hWnd, WINBOOL bRevert)
{
  return g_imports.user32.GetSystemMenu(hWnd, bRevert);
}

DLLEXPORT HMENU WINAPI CreateMenu (VOID)
{
  return g_imports.user32.CreateMenu();
}

DLLEXPORT HMENU WINAPI CreatePopupMenu (VOID)
{
  return g_imports.user32.CreatePopupMenu();
}

DLLEXPORT WINBOOL WINAPI DestroyMenu (HMENU hMenu)
{
  return g_imports.user32.DestroyMenu(hMenu);
}

DLLEXPORT DWORD WINAPI CheckMenuItem (HMENU hMenu, UINT uIDCheckItem, UINT uCheck)
{
  return g_imports.user32.CheckMenuItem(hMenu, uIDCheckItem, uCheck);
}

DLLEXPORT WINBOOL WINAPI EnableMenuItem (HMENU hMenu, UINT uIDEnableItem, UINT uEnable)
{
  return g_imports.user32.EnableMenuItem(hMenu, uIDEnableItem, uEnable);
}

DLLEXPORT HMENU WINAPI GetSubMenu (HMENU hMenu, int nPos)
{
  return g_imports.user32.GetSubMenu(hMenu, nPos);
}

DLLEXPORT UINT WINAPI GetMenuItemID (HMENU hMenu, int nPos)
{
  return g_imports.user32.GetMenuItemID(hMenu, nPos);
}

DLLEXPORT int WINAPI GetMenuItemCount (HMENU hMenu)
{
  return g_imports.user32.GetMenuItemCount(hMenu);
}

DLLEXPORT WINBOOL WINAPI InsertMenuA (HMENU hMenu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
{
  return g_imports.user32.InsertMenuA(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

DLLEXPORT WINBOOL WINAPI InsertMenuW (HMENU hMenu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
{
  return g_imports.user32.InsertMenuW(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

DLLEXPORT WINBOOL WINAPI AppendMenuA (HMENU hMenu, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
{
  return g_imports.user32.AppendMenuA(hMenu, uFlags, uIDNewItem, lpNewItem);
}

DLLEXPORT WINBOOL WINAPI AppendMenuW (HMENU hMenu, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
{
  return g_imports.user32.AppendMenuW(hMenu, uFlags, uIDNewItem, lpNewItem);
}

DLLEXPORT WINBOOL WINAPI ModifyMenuA (HMENU hMnu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
{
  return g_imports.user32.ModifyMenuA(hMnu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

DLLEXPORT WINBOOL WINAPI ModifyMenuW (HMENU hMnu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
{
  return g_imports.user32.ModifyMenuW(hMnu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

DLLEXPORT WINBOOL WINAPI RemoveMenu (HMENU hMenu, UINT uPosition, UINT uFlags)
{
  return g_imports.user32.RemoveMenu(hMenu, uPosition, uFlags);
}

DLLEXPORT WINBOOL WINAPI DeleteMenu (HMENU hMenu, UINT uPosition, UINT uFlags)
{
  return g_imports.user32.DeleteMenu(hMenu, uPosition, uFlags);
}

DLLEXPORT WINBOOL WINAPI SetMenuItemBitmaps (HMENU hMenu, UINT uPosition, UINT uFlags, HBITMAP hBitmapUnchecked, HBITMAP hBitmapChecked)
{
  return g_imports.user32.SetMenuItemBitmaps(hMenu, uPosition, uFlags, hBitmapUnchecked, hBitmapChecked);
}

DLLEXPORT LONG WINAPI GetMenuCheckMarkDimensions (VOID)
{
  return g_imports.user32.GetMenuCheckMarkDimensions();
}

DLLEXPORT WINBOOL WINAPI TrackPopupMenu (HMENU hMenu, UINT uFlags, int x, int y, int nReserved, HWND hWnd, CONST RECT * prcRect)
{
  return g_imports.user32.TrackPopupMenu(hMenu, uFlags, x, y, nReserved, hWnd, prcRect);
}

DLLEXPORT WINBOOL WINAPI TrackPopupMenuEx (HMENU arg0, UINT arg1, int arg2, int arg3, HWND arg4, LPTPMPARAMS arg5)
{
  return g_imports.user32.TrackPopupMenuEx(arg0, arg1, arg2, arg3, arg4, arg5);
}

DLLEXPORT WINBOOL WINAPI GetMenuInfo (HMENU arg0, LPMENUINFO arg1)
{
  return g_imports.user32.GetMenuInfo(arg0, arg1);
}

DLLEXPORT WINBOOL WINAPI SetMenuInfo (HMENU arg0, LPCMENUINFO arg1)
{
  return g_imports.user32.SetMenuInfo(arg0, arg1);
}

DLLEXPORT WINBOOL WINAPI EndMenu (VOID)
{
  return g_imports.user32.EndMenu();
}

DLLEXPORT WINBOOL WINAPI CalculatePopupWindowPosition (const POINT * anchorPoint, const SIZE * windowSize, UINT flags, RECT * excludeRect, RECT * popupWindowPosition)
{
  return g_imports.user32.CalculatePopupWindowPosition(anchorPoint, windowSize, flags, excludeRect, popupWindowPosition);
}

DLLEXPORT WINBOOL WINAPI InsertMenuItemA (HMENU hmenu, UINT item, WINBOOL fByPosition, LPCMENUITEMINFOA lpmi)
{
  return g_imports.user32.InsertMenuItemA(hmenu, item, fByPosition, lpmi);
}

DLLEXPORT WINBOOL WINAPI InsertMenuItemW (HMENU hmenu, UINT item, WINBOOL fByPosition, LPCMENUITEMINFOW lpmi)
{
  return g_imports.user32.InsertMenuItemW(hmenu, item, fByPosition, lpmi);
}

DLLEXPORT WINBOOL WINAPI GetMenuItemInfoA (HMENU hmenu, UINT item, WINBOOL fByPosition, LPMENUITEMINFOA lpmii)
{
  return g_imports.user32.GetMenuItemInfoA(hmenu, item, fByPosition, lpmii);
}

DLLEXPORT WINBOOL WINAPI GetMenuItemInfoW (HMENU hmenu, UINT item, WINBOOL fByPosition, LPMENUITEMINFOW lpmii)
{
  return g_imports.user32.GetMenuItemInfoW(hmenu, item, fByPosition, lpmii);
}

DLLEXPORT WINBOOL WINAPI SetMenuItemInfoA (HMENU hmenu, UINT item, WINBOOL fByPositon, LPCMENUITEMINFOA lpmii)
{
  return g_imports.user32.SetMenuItemInfoA(hmenu, item, fByPositon, lpmii);
}

DLLEXPORT WINBOOL WINAPI SetMenuItemInfoW (HMENU hmenu, UINT item, WINBOOL fByPositon, LPCMENUITEMINFOW lpmii)
{
  return g_imports.user32.SetMenuItemInfoW(hmenu, item, fByPositon, lpmii);
}

DLLEXPORT UINT WINAPI GetMenuDefaultItem (HMENU hMenu, UINT fByPos, UINT gmdiFlags)
{
  return g_imports.user32.GetMenuDefaultItem(hMenu, fByPos, gmdiFlags);
}

DLLEXPORT WINBOOL WINAPI SetMenuDefaultItem (HMENU hMenu, UINT uItem, UINT fByPos)
{
  return g_imports.user32.SetMenuDefaultItem(hMenu, uItem, fByPos);
}

DLLEXPORT WINBOOL WINAPI GetMenuItemRect (HWND hWnd, HMENU hMenu, UINT uItem, LPRECT lprcItem)
{
  return g_imports.user32.GetMenuItemRect(hWnd, hMenu, uItem, lprcItem);
}

DLLEXPORT int WINAPI MenuItemFromPoint (HWND hWnd, HMENU hMenu, POINT ptScreen)
{
  return g_imports.user32.MenuItemFromPoint(hWnd, hMenu, ptScreen);
}

DLLEXPORT DWORD WINAPI DragObject (HWND hwndParent, HWND hwndFrom, UINT fmt, ULONG_PTR data, HCURSOR hcur)
{
  return g_imports.user32.DragObject(hwndParent, hwndFrom, fmt, data, hcur);
}

DLLEXPORT WINBOOL WINAPI DragDetect (HWND hwnd, POINT pt)
{
  return g_imports.user32.DragDetect(hwnd, pt);
}

DLLEXPORT WINBOOL WINAPI DrawIcon (HDC hDC, int X, int Y, HICON hIcon)
{
  return g_imports.user32.DrawIcon(hDC, X, Y, hIcon);
}

DLLEXPORT int WINAPI DrawTextA (HDC hdc, LPCSTR lpchText, int cchText, LPRECT lprc, UINT format)
{
  return g_imports.user32.DrawTextA(hdc, lpchText, cchText, lprc, format);
}

DLLEXPORT int WINAPI DrawTextW (HDC hdc, LPCWSTR lpchText, int cchText, LPRECT lprc, UINT format)
{
  return g_imports.user32.DrawTextW(hdc, lpchText, cchText, lprc, format);
}

DLLEXPORT int WINAPI DrawTextExA (HDC hdc, LPSTR lpchText, int cchText, LPRECT lprc, UINT format, LPDRAWTEXTPARAMS lpdtp)
{
  return g_imports.user32.DrawTextExA(hdc, lpchText, cchText, lprc, format, lpdtp);
}

DLLEXPORT int WINAPI DrawTextExW (HDC hdc, LPWSTR lpchText, int cchText, LPRECT lprc, UINT format, LPDRAWTEXTPARAMS lpdtp)
{
  return g_imports.user32.DrawTextExW(hdc, lpchText, cchText, lprc, format, lpdtp);
}

DLLEXPORT WINBOOL WINAPI GrayStringA (HDC hDC, HBRUSH hBrush, GRAYSTRINGPROC lpOutputFunc, LPARAM lpData, int nCount, int X, int Y, int nWidth, int nHeight)
{
  return g_imports.user32.GrayStringA(hDC, hBrush, lpOutputFunc, lpData, nCount, X, Y, nWidth, nHeight);
}

DLLEXPORT WINBOOL WINAPI GrayStringW (HDC hDC, HBRUSH hBrush, GRAYSTRINGPROC lpOutputFunc, LPARAM lpData, int nCount, int X, int Y, int nWidth, int nHeight)
{
  return g_imports.user32.GrayStringW(hDC, hBrush, lpOutputFunc, lpData, nCount, X, Y, nWidth, nHeight);
}

DLLEXPORT WINBOOL WINAPI DrawStateA (HDC hdc, HBRUSH hbrFore, DRAWSTATEPROC qfnCallBack, LPARAM lData, WPARAM wData, int x, int y, int cx, int cy, UINT uFlags)
{
  return g_imports.user32.DrawStateA(hdc, hbrFore, qfnCallBack, lData, wData, x, y, cx, cy, uFlags);
}

DLLEXPORT WINBOOL WINAPI DrawStateW (HDC hdc, HBRUSH hbrFore, DRAWSTATEPROC qfnCallBack, LPARAM lData, WPARAM wData, int x, int y, int cx, int cy, UINT uFlags)
{
  return g_imports.user32.DrawStateW(hdc, hbrFore, qfnCallBack, lData, wData, x, y, cx, cy, uFlags);
}

DLLEXPORT LONG WINAPI TabbedTextOutA (HDC hdc, int x, int y, LPCSTR lpString, int chCount, int nTabPositions, CONST INT * lpnTabStopPositions, int nTabOrigin)
{
  return g_imports.user32.TabbedTextOutA(hdc, x, y, lpString, chCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
}

DLLEXPORT LONG WINAPI TabbedTextOutW (HDC hdc, int x, int y, LPCWSTR lpString, int chCount, int nTabPositions, CONST INT * lpnTabStopPositions, int nTabOrigin)
{
  return g_imports.user32.TabbedTextOutW(hdc, x, y, lpString, chCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
}

DLLEXPORT DWORD WINAPI GetTabbedTextExtentA (HDC hdc, LPCSTR lpString, int chCount, int nTabPositions, CONST INT * lpnTabStopPositions)
{
  return g_imports.user32.GetTabbedTextExtentA(hdc, lpString, chCount, nTabPositions, lpnTabStopPositions);
}

DLLEXPORT DWORD WINAPI GetTabbedTextExtentW (HDC hdc, LPCWSTR lpString, int chCount, int nTabPositions, CONST INT * lpnTabStopPositions)
{
  return g_imports.user32.GetTabbedTextExtentW(hdc, lpString, chCount, nTabPositions, lpnTabStopPositions);
}

DLLEXPORT WINBOOL WINAPI UpdateWindow (HWND hWnd)
{
  return g_imports.user32.UpdateWindow(hWnd);
}

DLLEXPORT HWND WINAPI SetActiveWindow (HWND hWnd)
{
  return g_imports.user32.SetActiveWindow(hWnd);
}

DLLEXPORT HWND WINAPI GetForegroundWindow (VOID)
{
  return g_imports.user32.GetForegroundWindow();
}

DLLEXPORT WINBOOL WINAPI PaintDesktop (HDC hdc)
{
  return g_imports.user32.PaintDesktop(hdc);
}

DLLEXPORT VOID WINAPI SwitchToThisWindow (HWND hwnd, WINBOOL fUnknown)
{
  g_imports.user32.SwitchToThisWindow(hwnd, fUnknown);
}

DLLEXPORT WINBOOL WINAPI SetForegroundWindow (HWND hWnd)
{
  return g_imports.user32.SetForegroundWindow(hWnd);
}

DLLEXPORT WINBOOL WINAPI AllowSetForegroundWindow (DWORD dwProcessId)
{
  return g_imports.user32.AllowSetForegroundWindow(dwProcessId);
}

DLLEXPORT WINBOOL WINAPI LockSetForegroundWindow (UINT uLockCode)
{
  return g_imports.user32.LockSetForegroundWindow(uLockCode);
}

DLLEXPORT HWND WINAPI WindowFromDC (HDC hDC)
{
  return g_imports.user32.WindowFromDC(hDC);
}

DLLEXPORT HDC WINAPI GetDC (HWND hWnd)
{
  return g_imports.user32.GetDC(hWnd);
}

DLLEXPORT HDC WINAPI GetDCEx (HWND hWnd, HRGN hrgnClip, DWORD flags)
{
  return g_imports.user32.GetDCEx(hWnd, hrgnClip, flags);
}

DLLEXPORT HDC WINAPI GetWindowDC (HWND hWnd)
{
  return g_imports.user32.GetWindowDC(hWnd);
}

DLLEXPORT int WINAPI ReleaseDC (HWND hWnd, HDC hDC)
{
  return g_imports.user32.ReleaseDC(hWnd, hDC);
}

DLLEXPORT HDC WINAPI BeginPaint (HWND hWnd, LPPAINTSTRUCT lpPaint)
{
  return g_imports.user32.BeginPaint(hWnd, lpPaint);
}

DLLEXPORT WINBOOL WINAPI EndPaint (HWND hWnd, CONST PAINTSTRUCT * lpPaint)
{
  return g_imports.user32.EndPaint(hWnd, lpPaint);
}

DLLEXPORT WINBOOL WINAPI GetUpdateRect (HWND hWnd, LPRECT lpRect, WINBOOL bErase)
{
  return g_imports.user32.GetUpdateRect(hWnd, lpRect, bErase);
}

DLLEXPORT int WINAPI GetUpdateRgn (HWND hWnd, HRGN hRgn, WINBOOL bErase)
{
  return g_imports.user32.GetUpdateRgn(hWnd, hRgn, bErase);
}

DLLEXPORT int WINAPI SetWindowRgn (HWND hWnd, HRGN hRgn, WINBOOL bRedraw)
{
  return g_imports.user32.SetWindowRgn(hWnd, hRgn, bRedraw);
}

DLLEXPORT int WINAPI GetWindowRgn (HWND hWnd, HRGN hRgn)
{
  return g_imports.user32.GetWindowRgn(hWnd, hRgn);
}

DLLEXPORT int WINAPI GetWindowRgnBox (HWND hWnd, LPRECT lprc)
{
  return g_imports.user32.GetWindowRgnBox(hWnd, lprc);
}

DLLEXPORT int WINAPI ExcludeUpdateRgn (HDC hDC, HWND hWnd)
{
  return g_imports.user32.ExcludeUpdateRgn(hDC, hWnd);
}

DLLEXPORT WINBOOL WINAPI InvalidateRect (HWND hWnd, CONST RECT * lpRect, WINBOOL bErase)
{
  return g_imports.user32.InvalidateRect(hWnd, lpRect, bErase);
}

DLLEXPORT WINBOOL WINAPI ValidateRect (HWND hWnd, CONST RECT * lpRect)
{
  return g_imports.user32.ValidateRect(hWnd, lpRect);
}

DLLEXPORT WINBOOL WINAPI InvalidateRgn (HWND hWnd, HRGN hRgn, WINBOOL bErase)
{
  return g_imports.user32.InvalidateRgn(hWnd, hRgn, bErase);
}

DLLEXPORT WINBOOL WINAPI ValidateRgn (HWND hWnd, HRGN hRgn)
{
  return g_imports.user32.ValidateRgn(hWnd, hRgn);
}

DLLEXPORT WINBOOL WINAPI RedrawWindow (HWND hWnd, CONST RECT * lprcUpdate, HRGN hrgnUpdate, UINT flags)
{
  return g_imports.user32.RedrawWindow(hWnd, lprcUpdate, hrgnUpdate, flags);
}

DLLEXPORT WINBOOL WINAPI LockWindowUpdate (HWND hWndLock)
{
  return g_imports.user32.LockWindowUpdate(hWndLock);
}

DLLEXPORT WINBOOL WINAPI ScrollWindow (HWND hWnd, int XAmount, int YAmount, CONST RECT * lpRect, CONST RECT * lpClipRect)
{
  return g_imports.user32.ScrollWindow(hWnd, XAmount, YAmount, lpRect, lpClipRect);
}

DLLEXPORT WINBOOL WINAPI ScrollDC (HDC hDC, int dx, int dy, CONST RECT * lprcScroll, CONST RECT * lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate)
{
  return g_imports.user32.ScrollDC(hDC, dx, dy, lprcScroll, lprcClip, hrgnUpdate, lprcUpdate);
}

DLLEXPORT int WINAPI ScrollWindowEx (HWND hWnd, int dx, int dy, CONST RECT * prcScroll, CONST RECT * prcClip, HRGN hrgnUpdate, LPRECT prcUpdate, UINT flags)
{
  return g_imports.user32.ScrollWindowEx(hWnd, dx, dy, prcScroll, prcClip, hrgnUpdate, prcUpdate, flags);
}

DLLEXPORT int WINAPI SetScrollPos (HWND hWnd, int nBar, int nPos, WINBOOL bRedraw)
{
  return g_imports.user32.SetScrollPos(hWnd, nBar, nPos, bRedraw);
}

DLLEXPORT int WINAPI GetScrollPos (HWND hWnd, int nBar)
{
  return g_imports.user32.GetScrollPos(hWnd, nBar);
}

DLLEXPORT WINBOOL WINAPI SetScrollRange (HWND hWnd, int nBar, int nMinPos, int nMaxPos, WINBOOL bRedraw)
{
  return g_imports.user32.SetScrollRange(hWnd, nBar, nMinPos, nMaxPos, bRedraw);
}

DLLEXPORT WINBOOL WINAPI GetScrollRange (HWND hWnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos)
{
  return g_imports.user32.GetScrollRange(hWnd, nBar, lpMinPos, lpMaxPos);
}

DLLEXPORT WINBOOL WINAPI ShowScrollBar (HWND hWnd, int wBar, WINBOOL bShow)
{
  return g_imports.user32.ShowScrollBar(hWnd, wBar, bShow);
}

DLLEXPORT WINBOOL WINAPI EnableScrollBar (HWND hWnd, UINT wSBflags, UINT wArrows)
{
  return g_imports.user32.EnableScrollBar(hWnd, wSBflags, wArrows);
}

DLLEXPORT WINBOOL WINAPI SetPropA (HWND hWnd, LPCSTR lpString, HANDLE hData)
{
  return g_imports.user32.SetPropA(hWnd, lpString, hData);
}

DLLEXPORT WINBOOL WINAPI SetPropW (HWND hWnd, LPCWSTR lpString, HANDLE hData)
{
  return g_imports.user32.SetPropW(hWnd, lpString, hData);
}

DLLEXPORT HANDLE WINAPI GetPropA (HWND hWnd, LPCSTR lpString)
{
  return g_imports.user32.GetPropA(hWnd, lpString);
}

DLLEXPORT HANDLE WINAPI GetPropW (HWND hWnd, LPCWSTR lpString)
{
  return g_imports.user32.GetPropW(hWnd, lpString);
}

DLLEXPORT HANDLE WINAPI RemovePropA (HWND hWnd, LPCSTR lpString)
{
  return g_imports.user32.RemovePropA(hWnd, lpString);
}

DLLEXPORT HANDLE WINAPI RemovePropW (HWND hWnd, LPCWSTR lpString)
{
  return g_imports.user32.RemovePropW(hWnd, lpString);
}

DLLEXPORT int WINAPI EnumPropsExA (HWND hWnd, PROPENUMPROCEXA lpEnumFunc, LPARAM lParam)
{
  return g_imports.user32.EnumPropsExA(hWnd, lpEnumFunc, lParam);
}

DLLEXPORT int WINAPI EnumPropsExW (HWND hWnd, PROPENUMPROCEXW lpEnumFunc, LPARAM lParam)
{
  return g_imports.user32.EnumPropsExW(hWnd, lpEnumFunc, lParam);
}

DLLEXPORT int WINAPI EnumPropsA (HWND hWnd, PROPENUMPROCA lpEnumFunc)
{
  return g_imports.user32.EnumPropsA(hWnd, lpEnumFunc);
}

DLLEXPORT int WINAPI EnumPropsW (HWND hWnd, PROPENUMPROCW lpEnumFunc)
{
  return g_imports.user32.EnumPropsW(hWnd, lpEnumFunc);
}

DLLEXPORT WINBOOL WINAPI SetWindowTextA (HWND hWnd, LPCSTR lpString)
{
  return g_imports.user32.SetWindowTextA(hWnd, lpString);
}

DLLEXPORT WINBOOL WINAPI SetWindowTextW (HWND hWnd, LPCWSTR lpString)
{
  return g_imports.user32.SetWindowTextW(hWnd, lpString);
}

DLLEXPORT int WINAPI GetWindowTextA (HWND hWnd, LPSTR lpString, int nMaxCount)
{
  return g_imports.user32.GetWindowTextA(hWnd, lpString, nMaxCount);
}

DLLEXPORT int WINAPI GetWindowTextW (HWND hWnd, LPWSTR lpString, int nMaxCount)
{
  return g_imports.user32.GetWindowTextW(hWnd, lpString, nMaxCount);
}

DLLEXPORT int WINAPI GetWindowTextLengthA (HWND hWnd)
{
  return g_imports.user32.GetWindowTextLengthA(hWnd);
}

DLLEXPORT int WINAPI GetWindowTextLengthW (HWND hWnd)
{
  return g_imports.user32.GetWindowTextLengthW(hWnd);
}

DLLEXPORT WINBOOL WINAPI GetClientRect (HWND hWnd, LPRECT lpRect)
{
  return g_imports.user32.GetClientRect(hWnd, lpRect);
}

DLLEXPORT WINBOOL WINAPI GetWindowRect (HWND hWnd, LPRECT lpRect)
{
  return g_imports.user32.GetWindowRect(hWnd, lpRect);
}

DLLEXPORT WINBOOL WINAPI AdjustWindowRect (LPRECT lpRect, DWORD dwStyle, WINBOOL bMenu)
{
  return g_imports.user32.AdjustWindowRect(lpRect, dwStyle, bMenu);
}

DLLEXPORT WINBOOL WINAPI AdjustWindowRectEx (LPRECT lpRect, DWORD dwStyle, WINBOOL bMenu, DWORD dwExStyle)
{
  return g_imports.user32.AdjustWindowRectEx(lpRect, dwStyle, bMenu, dwExStyle);
}

DLLEXPORT WINBOOL WINAPI SetWindowContextHelpId (HWND arg0, DWORD arg1)
{
  return g_imports.user32.SetWindowContextHelpId(arg0, arg1);
}

DLLEXPORT DWORD WINAPI GetWindowContextHelpId (HWND arg0)
{
  return g_imports.user32.GetWindowContextHelpId(arg0);
}

DLLEXPORT WINBOOL WINAPI SetMenuContextHelpId (HMENU arg0, DWORD arg1)
{
  return g_imports.user32.SetMenuContextHelpId(arg0, arg1);
}

DLLEXPORT DWORD WINAPI GetMenuContextHelpId (HMENU arg0)
{
  return g_imports.user32.GetMenuContextHelpId(arg0);
}

DLLEXPORT int WINAPI MessageBoxA (HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
  return g_imports.user32.MessageBoxA(hWnd, lpText, lpCaption, uType);
}

DLLEXPORT int WINAPI MessageBoxW (HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
  return g_imports.user32.MessageBoxW(hWnd, lpText, lpCaption, uType);
}

DLLEXPORT int WINAPI MessageBoxExA (HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId)
{
  return g_imports.user32.MessageBoxExA(hWnd, lpText, lpCaption, uType, wLanguageId);
}

DLLEXPORT int WINAPI MessageBoxExW (HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType, WORD wLanguageId)
{
  return g_imports.user32.MessageBoxExW(hWnd, lpText, lpCaption, uType, wLanguageId);
}

DLLEXPORT int WINAPI MessageBoxIndirectA (CONST MSGBOXPARAMSA * lpmbp)
{
  return g_imports.user32.MessageBoxIndirectA(lpmbp);
}

DLLEXPORT int WINAPI MessageBoxIndirectW (CONST MSGBOXPARAMSW * lpmbp)
{
  return g_imports.user32.MessageBoxIndirectW(lpmbp);
}

DLLEXPORT WINBOOL WINAPI MessageBeep (UINT uType)
{
  return g_imports.user32.MessageBeep(uType);
}

DLLEXPORT int WINAPI ShowCursor (WINBOOL bShow)
{
  return g_imports.user32.ShowCursor(bShow);
}

DLLEXPORT WINBOOL WINAPI SetCursorPos (int X, int Y)
{
  return g_imports.user32.SetCursorPos(X, Y);
}

DLLEXPORT HCURSOR WINAPI SetCursor (HCURSOR hCursor)
{
  return g_imports.user32.SetCursor(hCursor);
}

DLLEXPORT WINBOOL WINAPI GetCursorPos (LPPOINT lpPoint)
{
  return g_imports.user32.GetCursorPos(lpPoint);
}

DLLEXPORT WINBOOL WINAPI ClipCursor (CONST RECT * lpRect)
{
  return g_imports.user32.ClipCursor(lpRect);
}

DLLEXPORT WINBOOL WINAPI GetClipCursor (LPRECT lpRect)
{
  return g_imports.user32.GetClipCursor(lpRect);
}

DLLEXPORT HCURSOR WINAPI GetCursor (VOID)
{
  return g_imports.user32.GetCursor();
}

DLLEXPORT WINBOOL WINAPI CreateCaret (HWND hWnd, HBITMAP hBitmap, int nWidth, int nHeight)
{
  return g_imports.user32.CreateCaret(hWnd, hBitmap, nWidth, nHeight);
}

DLLEXPORT UINT WINAPI GetCaretBlinkTime (VOID)
{
  return g_imports.user32.GetCaretBlinkTime();
}

DLLEXPORT WINBOOL WINAPI SetCaretBlinkTime (UINT uMSeconds)
{
  return g_imports.user32.SetCaretBlinkTime(uMSeconds);
}

DLLEXPORT WINBOOL WINAPI DestroyCaret (VOID)
{
  return g_imports.user32.DestroyCaret();
}

DLLEXPORT WINBOOL WINAPI HideCaret (HWND hWnd)
{
  return g_imports.user32.HideCaret(hWnd);
}

DLLEXPORT WINBOOL WINAPI ShowCaret (HWND hWnd)
{
  return g_imports.user32.ShowCaret(hWnd);
}

DLLEXPORT WINBOOL WINAPI SetCaretPos (int X, int Y)
{
  return g_imports.user32.SetCaretPos(X, Y);
}

DLLEXPORT WINBOOL WINAPI GetCaretPos (LPPOINT lpPoint)
{
  return g_imports.user32.GetCaretPos(lpPoint);
}

DLLEXPORT WINBOOL WINAPI ClientToScreen (HWND hWnd, LPPOINT lpPoint)
{
  return g_imports.user32.ClientToScreen(hWnd, lpPoint);
}

DLLEXPORT WINBOOL WINAPI ScreenToClient (HWND hWnd, LPPOINT lpPoint)
{
  return g_imports.user32.ScreenToClient(hWnd, lpPoint);
}

DLLEXPORT int WINAPI MapWindowPoints (HWND hWndFrom, HWND hWndTo, LPPOINT lpPoints, UINT cPoints)
{
  return g_imports.user32.MapWindowPoints(hWndFrom, hWndTo, lpPoints, cPoints);
}

DLLEXPORT HWND WINAPI WindowFromPoint (POINT Point)
{
  return g_imports.user32.WindowFromPoint(Point);
}

DLLEXPORT HWND WINAPI ChildWindowFromPoint (HWND hWndParent, POINT Point)
{
  return g_imports.user32.ChildWindowFromPoint(hWndParent, Point);
}

DLLEXPORT HWND WINAPI ChildWindowFromPointEx (HWND hwnd, POINT pt, UINT flags)
{
  return g_imports.user32.ChildWindowFromPointEx(hwnd, pt, flags);
}

DLLEXPORT WINBOOL WINAPI SetPhysicalCursorPos (int X, int Y)
{
  return g_imports.user32.SetPhysicalCursorPos(X, Y);
}

DLLEXPORT WINBOOL WINAPI GetPhysicalCursorPos (LPPOINT lpPoint)
{
  return g_imports.user32.GetPhysicalCursorPos(lpPoint);
}

DLLEXPORT WINBOOL WINAPI LogicalToPhysicalPoint (HWND hWnd, LPPOINT lpPoint)
{
  return g_imports.user32.LogicalToPhysicalPoint(hWnd, lpPoint);
}

DLLEXPORT WINBOOL WINAPI PhysicalToLogicalPoint (HWND hWnd, LPPOINT lpPoint)
{
  return g_imports.user32.PhysicalToLogicalPoint(hWnd, lpPoint);
}

DLLEXPORT HWND WINAPI WindowFromPhysicalPoint (POINT Point)
{
  return g_imports.user32.WindowFromPhysicalPoint(Point);
}

DLLEXPORT DWORD WINAPI GetSysColor (int nIndex)
{
  return g_imports.user32.GetSysColor(nIndex);
}

DLLEXPORT HBRUSH WINAPI GetSysColorBrush (int nIndex)
{
  return g_imports.user32.GetSysColorBrush(nIndex);
}

DLLEXPORT WINBOOL WINAPI SetSysColors (int cElements, CONST INT * lpaElements, CONST COLORREF * lpaRgbValues)
{
  return g_imports.user32.SetSysColors(cElements, lpaElements, lpaRgbValues);
}

DLLEXPORT WINBOOL WINAPI DrawFocusRect (HDC hDC, CONST RECT * lprc)
{
  return g_imports.user32.DrawFocusRect(hDC, lprc);
}

DLLEXPORT int WINAPI FillRect (HDC hDC, CONST RECT * lprc, HBRUSH hbr)
{
  return g_imports.user32.FillRect(hDC, lprc, hbr);
}

DLLEXPORT int WINAPI FrameRect (HDC hDC, CONST RECT * lprc, HBRUSH hbr)
{
  return g_imports.user32.FrameRect(hDC, lprc, hbr);
}

DLLEXPORT WINBOOL WINAPI InvertRect (HDC hDC, CONST RECT * lprc)
{
  return g_imports.user32.InvertRect(hDC, lprc);
}

DLLEXPORT WINBOOL WINAPI SetRect (LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom)
{
  return g_imports.user32.SetRect(lprc, xLeft, yTop, xRight, yBottom);
}

DLLEXPORT WINBOOL WINAPI SetRectEmpty (LPRECT lprc)
{
  return g_imports.user32.SetRectEmpty(lprc);
}

DLLEXPORT WINBOOL WINAPI CopyRect (LPRECT lprcDst, CONST RECT * lprcSrc)
{
  return g_imports.user32.CopyRect(lprcDst, lprcSrc);
}

DLLEXPORT WINBOOL WINAPI InflateRect (LPRECT lprc, int dx, int dy)
{
  return g_imports.user32.InflateRect(lprc, dx, dy);
}

DLLEXPORT WINBOOL WINAPI IntersectRect (LPRECT lprcDst, CONST RECT * lprcSrc1, CONST RECT * lprcSrc2)
{
  return g_imports.user32.IntersectRect(lprcDst, lprcSrc1, lprcSrc2);
}

DLLEXPORT WINBOOL WINAPI UnionRect (LPRECT lprcDst, CONST RECT * lprcSrc1, CONST RECT * lprcSrc2)
{
  return g_imports.user32.UnionRect(lprcDst, lprcSrc1, lprcSrc2);
}

DLLEXPORT WINBOOL WINAPI SubtractRect (LPRECT lprcDst, CONST RECT * lprcSrc1, CONST RECT * lprcSrc2)
{
  return g_imports.user32.SubtractRect(lprcDst, lprcSrc1, lprcSrc2);
}

DLLEXPORT WINBOOL WINAPI OffsetRect (LPRECT lprc, int dx, int dy)
{
  return g_imports.user32.OffsetRect(lprc, dx, dy);
}

DLLEXPORT WINBOOL WINAPI IsRectEmpty (CONST RECT * lprc)
{
  return g_imports.user32.IsRectEmpty(lprc);
}

DLLEXPORT WINBOOL WINAPI EqualRect (CONST RECT * lprc1, CONST RECT * lprc2)
{
  return g_imports.user32.EqualRect(lprc1, lprc2);
}

DLLEXPORT WINBOOL WINAPI PtInRect (CONST RECT * lprc, POINT pt)
{
  return g_imports.user32.PtInRect(lprc, pt);
}

DLLEXPORT WORD WINAPI GetWindowWord (HWND hWnd, int nIndex)
{
  return g_imports.user32.GetWindowWord(hWnd, nIndex);
}

DLLEXPORT WORD WINAPI SetWindowWord (HWND hWnd, int nIndex, WORD wNewWord)
{
  return g_imports.user32.SetWindowWord(hWnd, nIndex, wNewWord);
}

DLLEXPORT LONG WINAPI GetWindowLongA (HWND hWnd, int nIndex)
{
  return g_imports.user32.GetWindowLongA(hWnd, nIndex);
}

DLLEXPORT LONG WINAPI GetWindowLongW (HWND hWnd, int nIndex)
{
  return g_imports.user32.GetWindowLongW(hWnd, nIndex);
}

DLLEXPORT LONG WINAPI SetWindowLongA (HWND hWnd, int nIndex, LONG dwNewLong)
{
  return g_imports.user32.SetWindowLongA(hWnd, nIndex, dwNewLong);
}

DLLEXPORT LONG WINAPI SetWindowLongW (HWND hWnd, int nIndex, LONG dwNewLong)
{
  return g_imports.user32.SetWindowLongW(hWnd, nIndex, dwNewLong);
}

#ifdef _WIN64
DLLEXPORT LONG_PTR WINAPI GetWindowLongPtrA (HWND hWnd, int nIndex)
{
  return g_imports.user32.GetWindowLongPtrA(hWnd, nIndex);
}

DLLEXPORT LONG_PTR WINAPI GetWindowLongPtrW (HWND hWnd, int nIndex)
{
  return g_imports.user32.GetWindowLongPtrW(hWnd, nIndex);
}

DLLEXPORT LONG_PTR WINAPI SetWindowLongPtrA (HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
  return g_imports.user32.SetWindowLongPtrA(hWnd, nIndex, dwNewLong);
}

DLLEXPORT LONG_PTR WINAPI SetWindowLongPtrW (HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
  return g_imports.user32.SetWindowLongPtrW(hWnd, nIndex, dwNewLong);
}
#endif

DLLEXPORT WORD WINAPI GetClassWord (HWND hWnd, int nIndex)
{
  return g_imports.user32.GetClassWord(hWnd, nIndex);
}

DLLEXPORT WORD WINAPI SetClassWord (HWND hWnd, int nIndex, WORD wNewWord)
{
  return g_imports.user32.SetClassWord(hWnd, nIndex, wNewWord);
}

DLLEXPORT DWORD WINAPI GetClassLongA (HWND hWnd, int nIndex)
{
  return g_imports.user32.GetClassLongA(hWnd, nIndex);
}

DLLEXPORT DWORD WINAPI GetClassLongW (HWND hWnd, int nIndex)
{
  return g_imports.user32.GetClassLongW(hWnd, nIndex);
}

DLLEXPORT DWORD WINAPI SetClassLongA (HWND hWnd, int nIndex, LONG dwNewLong)
{
  return g_imports.user32.SetClassLongA(hWnd, nIndex, dwNewLong);
}

DLLEXPORT DWORD WINAPI SetClassLongW (HWND hWnd, int nIndex, LONG dwNewLong)
{
  return g_imports.user32.SetClassLongW(hWnd, nIndex, dwNewLong);
}

#ifdef _WIN64
DLLEXPORT ULONG_PTR WINAPI GetClassLongPtrA (HWND hWnd, int nIndex)
{
  return g_imports.user32.GetClassLongPtrA(hWnd, nIndex);
}

DLLEXPORT ULONG_PTR WINAPI GetClassLongPtrW (HWND hWnd, int nIndex)
{
  return g_imports.user32.GetClassLongPtrW(hWnd, nIndex);
}

DLLEXPORT ULONG_PTR WINAPI SetClassLongPtrA (HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
  return g_imports.user32.SetClassLongPtrA(hWnd, nIndex, dwNewLong);
}

DLLEXPORT ULONG_PTR WINAPI SetClassLongPtrW (HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
  return g_imports.user32.SetClassLongPtrW(hWnd, nIndex, dwNewLong);
}
#endif

DLLEXPORT WINBOOL WINAPI GetProcessDefaultLayout (DWORD * pdwDefaultLayout)
{
  return g_imports.user32.GetProcessDefaultLayout(pdwDefaultLayout);
}

DLLEXPORT WINBOOL WINAPI SetProcessDefaultLayout (DWORD dwDefaultLayout)
{
  return g_imports.user32.SetProcessDefaultLayout(dwDefaultLayout);
}

DLLEXPORT HWND WINAPI GetDesktopWindow (VOID)
{
  return g_imports.user32.GetDesktopWindow();
}

DLLEXPORT HWND WINAPI GetParent (HWND hWnd)
{
  return g_imports.user32.GetParent(hWnd);
}

DLLEXPORT HWND WINAPI SetParent (HWND hWndChild, HWND hWndNewParent)
{
  return g_imports.user32.SetParent(hWndChild, hWndNewParent);
}

DLLEXPORT WINBOOL WINAPI EnumChildWindows (HWND hWndParent, WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
  return g_imports.user32.EnumChildWindows(hWndParent, lpEnumFunc, lParam);
}

DLLEXPORT HWND WINAPI FindWindowA (LPCSTR lpClassName, LPCSTR lpWindowName)
{
  return g_imports.user32.FindWindowA(lpClassName, lpWindowName);
}

DLLEXPORT HWND WINAPI FindWindowW (LPCWSTR lpClassName, LPCWSTR lpWindowName)
{
  return g_imports.user32.FindWindowW(lpClassName, lpWindowName);
}

DLLEXPORT HWND WINAPI FindWindowExA (HWND hWndParent, HWND hWndChildAfter, LPCSTR lpszClass, LPCSTR lpszWindow)
{
  return g_imports.user32.FindWindowExA(hWndParent, hWndChildAfter, lpszClass, lpszWindow);
}

DLLEXPORT HWND WINAPI FindWindowExW (HWND hWndParent, HWND hWndChildAfter, LPCWSTR lpszClass, LPCWSTR lpszWindow)
{
  return g_imports.user32.FindWindowExW(hWndParent, hWndChildAfter, lpszClass, lpszWindow);
}

DLLEXPORT HWND WINAPI GetShellWindow (VOID)
{
  return g_imports.user32.GetShellWindow();
}

DLLEXPORT WINBOOL WINAPI RegisterShellHookWindow (HWND hwnd)
{
  return g_imports.user32.RegisterShellHookWindow(hwnd);
}

DLLEXPORT WINBOOL WINAPI DeregisterShellHookWindow (HWND hwnd)
{
  return g_imports.user32.DeregisterShellHookWindow(hwnd);
}

DLLEXPORT WINBOOL WINAPI EnumWindows (WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
  return g_imports.user32.EnumWindows(lpEnumFunc, lParam);
}

DLLEXPORT WINBOOL WINAPI EnumThreadWindows (DWORD dwThreadId, WNDENUMPROC lpfn, LPARAM lParam)
{
  return g_imports.user32.EnumThreadWindows(dwThreadId, lpfn, lParam);
}

DLLEXPORT int WINAPI GetClassNameA (HWND hWnd, LPSTR lpClassName, int nMaxCount)
{
  return g_imports.user32.GetClassNameA(hWnd, lpClassName, nMaxCount);
}

DLLEXPORT int WINAPI GetClassNameW (HWND hWnd, LPWSTR lpClassName, int nMaxCount)
{
  return g_imports.user32.GetClassNameW(hWnd, lpClassName, nMaxCount);
}

DLLEXPORT HWND WINAPI GetTopWindow (HWND hWnd)
{
  return g_imports.user32.GetTopWindow(hWnd);
}

DLLEXPORT DWORD WINAPI GetWindowThreadProcessId (HWND hWnd, LPDWORD lpdwProcessId)
{
  return g_imports.user32.GetWindowThreadProcessId(hWnd, lpdwProcessId);
}

DLLEXPORT WINBOOL WINAPI IsGUIThread (WINBOOL bConvert)
{
  return g_imports.user32.IsGUIThread(bConvert);
}

DLLEXPORT HWND WINAPI GetLastActivePopup (HWND hWnd)
{
  return g_imports.user32.GetLastActivePopup(hWnd);
}

DLLEXPORT HWND WINAPI GetWindow (HWND hWnd, UINT uCmd)
{
  return g_imports.user32.GetWindow(hWnd, uCmd);
}

#ifdef STRICT
DLLEXPORT HHOOK WINAPI SetWindowsHookA (int nFilterType, HOOKPROC pfnFilterProc)
{
  return g_imports.user32.SetWindowsHookA(nFilterType, pfnFilterProc);
}

DLLEXPORT HHOOK WINAPI SetWindowsHookW (int nFilterType, HOOKPROC pfnFilterProc)
{
  return g_imports.user32.SetWindowsHookW(nFilterType, pfnFilterProc);
}

#else

DLLEXPORT HOOKPROC WINAPI SetWindowsHookA (int nFilterType, HOOKPROC pfnFilterProc)
{
  return g_imports.user32.SetWindowsHookA(nFilterType, pfnFilterProc);
}

DLLEXPORT HOOKPROC WINAPI SetWindowsHookW (int nFilterType, HOOKPROC pfnFilterProc)
{
  return g_imports.user32.SetWindowsHookW(nFilterType, pfnFilterProc);
}

#endif

DLLEXPORT WINBOOL WINAPI UnhookWindowsHook (int nCode, HOOKPROC pfnFilterProc)
{
  return g_imports.user32.UnhookWindowsHook(nCode, pfnFilterProc);
}

DLLEXPORT HHOOK WINAPI SetWindowsHookExA (int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId)
{
  return g_imports.user32.SetWindowsHookExA(idHook, lpfn, hmod, dwThreadId);
}

DLLEXPORT HHOOK WINAPI SetWindowsHookExW (int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId)
{
  return g_imports.user32.SetWindowsHookExW(idHook, lpfn, hmod, dwThreadId);
}

DLLEXPORT WINBOOL WINAPI UnhookWindowsHookEx (HHOOK hhk)
{
  return g_imports.user32.UnhookWindowsHookEx(hhk);
}

DLLEXPORT LRESULT WINAPI CallNextHookEx (HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.CallNextHookEx(hhk, nCode, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI CheckMenuRadioItem (HMENU hmenu, UINT first, UINT last, UINT check, UINT flags)
{
  return g_imports.user32.CheckMenuRadioItem(hmenu, first, last, check, flags);
}

DLLEXPORT HBITMAP WINAPI LoadBitmapA (HINSTANCE hInstance, LPCSTR lpBitmapName)
{
  return g_imports.user32.LoadBitmapA(hInstance, lpBitmapName);
}

DLLEXPORT HBITMAP WINAPI LoadBitmapW (HINSTANCE hInstance, LPCWSTR lpBitmapName)
{
  return g_imports.user32.LoadBitmapW(hInstance, lpBitmapName);
}

DLLEXPORT HCURSOR WINAPI LoadCursorA (HINSTANCE hInstance, LPCSTR lpCursorName)
{
  return g_imports.user32.LoadCursorA(hInstance, lpCursorName);
}

DLLEXPORT HCURSOR WINAPI LoadCursorW (HINSTANCE hInstance, LPCWSTR lpCursorName)
{
  return g_imports.user32.LoadCursorW(hInstance, lpCursorName);
}

DLLEXPORT HCURSOR WINAPI LoadCursorFromFileA (LPCSTR lpFileName)
{
  return g_imports.user32.LoadCursorFromFileA(lpFileName);
}

DLLEXPORT HCURSOR WINAPI LoadCursorFromFileW (LPCWSTR lpFileName)
{
  return g_imports.user32.LoadCursorFromFileW(lpFileName);
}

DLLEXPORT HCURSOR WINAPI CreateCursor (HINSTANCE hInst, int xHotSpot, int yHotSpot, int nWidth, int nHeight, CONST VOID * pvANDPlane, CONST VOID * pvXORPlane)
{
  return g_imports.user32.CreateCursor(hInst, xHotSpot, yHotSpot, nWidth, nHeight, pvANDPlane, pvXORPlane);
}

DLLEXPORT WINBOOL WINAPI DestroyCursor (HCURSOR hCursor)
{
  return g_imports.user32.DestroyCursor(hCursor);
}

DLLEXPORT WINBOOL WINAPI SetSystemCursor (HCURSOR hcur, DWORD id)
{
  return g_imports.user32.SetSystemCursor(hcur, id);
}

DLLEXPORT HICON WINAPI LoadIconA (HINSTANCE hInstance, LPCSTR lpIconName)
{
  return g_imports.user32.LoadIconA(hInstance, lpIconName);
}

DLLEXPORT HICON WINAPI LoadIconW (HINSTANCE hInstance, LPCWSTR lpIconName)
{
  return g_imports.user32.LoadIconW(hInstance, lpIconName);
}

DLLEXPORT UINT WINAPI PrivateExtractIconsA (LPCSTR szFileName, int nIconIndex, int cxIcon, int cyIcon, HICON * phicon, UINT * piconid, UINT nIcons, UINT flags)
{
  return g_imports.user32.PrivateExtractIconsA(szFileName, nIconIndex, cxIcon, cyIcon, phicon, piconid, nIcons, flags);
}

DLLEXPORT UINT WINAPI PrivateExtractIconsW (LPCWSTR szFileName, int nIconIndex, int cxIcon, int cyIcon, HICON * phicon, UINT * piconid, UINT nIcons, UINT flags)
{
  return g_imports.user32.PrivateExtractIconsW(szFileName, nIconIndex, cxIcon, cyIcon, phicon, piconid, nIcons, flags);
}

DLLEXPORT HICON WINAPI CreateIcon (HINSTANCE hInstance, int nWidth, int nHeight, BYTE cPlanes, BYTE cBitsPixel, CONST BYTE * lpbANDbits, CONST BYTE * lpbXORbits)
{
  return g_imports.user32.CreateIcon(hInstance, nWidth, nHeight, cPlanes, cBitsPixel, lpbANDbits, lpbXORbits);
}

DLLEXPORT WINBOOL WINAPI DestroyIcon (HICON hIcon)
{
  return g_imports.user32.DestroyIcon(hIcon);
}

DLLEXPORT int WINAPI LookupIconIdFromDirectory (PBYTE presbits, WINBOOL fIcon)
{
  return g_imports.user32.LookupIconIdFromDirectory(presbits, fIcon);
}

DLLEXPORT int WINAPI LookupIconIdFromDirectoryEx (PBYTE presbits, WINBOOL fIcon, int cxDesired, int cyDesired, UINT Flags)
{
  return g_imports.user32.LookupIconIdFromDirectoryEx(presbits, fIcon, cxDesired, cyDesired, Flags);
}

DLLEXPORT HICON WINAPI CreateIconFromResource (PBYTE presbits, DWORD dwResSize, WINBOOL fIcon, DWORD dwVer)
{
  return g_imports.user32.CreateIconFromResource(presbits, dwResSize, fIcon, dwVer);
}

DLLEXPORT HICON WINAPI CreateIconFromResourceEx (PBYTE presbits, DWORD dwResSize, WINBOOL fIcon, DWORD dwVer, int cxDesired, int cyDesired, UINT Flags)
{
  return g_imports.user32.CreateIconFromResourceEx(presbits, dwResSize, fIcon, dwVer, cxDesired, cyDesired, Flags);
}

DLLEXPORT HANDLE WINAPI LoadImageA (HINSTANCE hInst, LPCSTR name, UINT type, int cx, int cy, UINT fuLoad)
{
  return g_imports.user32.LoadImageA(hInst, name, type, cx, cy, fuLoad);
}

DLLEXPORT HANDLE WINAPI LoadImageW (HINSTANCE hInst, LPCWSTR name, UINT type, int cx, int cy, UINT fuLoad)
{
  return g_imports.user32.LoadImageW(hInst, name, type, cx, cy, fuLoad);
}

DLLEXPORT HANDLE WINAPI CopyImage (HANDLE h, UINT type, int cx, int cy, UINT flags)
{
  return g_imports.user32.CopyImage(h, type, cx, cy, flags);
}

DLLEXPORT WINBOOL WINAPI DrawIconEx (HDC hdc, int xLeft, int yTop, HICON hIcon, int cxWidth, int cyWidth, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
{
  return g_imports.user32.DrawIconEx(hdc, xLeft, yTop, hIcon, cxWidth, cyWidth, istepIfAniCur, hbrFlickerFreeDraw, diFlags);
}

DLLEXPORT HICON WINAPI CreateIconIndirect (PICONINFO piconinfo)
{
  return g_imports.user32.CreateIconIndirect(piconinfo);
}

DLLEXPORT HICON WINAPI CopyIcon (HICON hIcon)
{
  return g_imports.user32.CopyIcon(hIcon);
}

DLLEXPORT WINBOOL WINAPI GetIconInfo (HICON hIcon, PICONINFO piconinfo)
{
  return g_imports.user32.GetIconInfo(hIcon, piconinfo);
}

DLLEXPORT WINBOOL WINAPI GetIconInfoExA (HICON hicon, PICONINFOEXA piconinfo)
{
  return g_imports.user32.GetIconInfoExA(hicon, piconinfo);
}

DLLEXPORT WINBOOL WINAPI GetIconInfoExW (HICON hicon, PICONINFOEXW piconinfo)
{
  return g_imports.user32.GetIconInfoExW(hicon, piconinfo);
}

DLLEXPORT int WINAPI LoadStringA (HINSTANCE hInstance, UINT uID, LPSTR lpBuffer, int cchBufferMax)
{
  return g_imports.user32.LoadStringA(hInstance, uID, lpBuffer, cchBufferMax);
}

DLLEXPORT int WINAPI LoadStringW (HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int cchBufferMax)
{
  return g_imports.user32.LoadStringW(hInstance, uID, lpBuffer, cchBufferMax);
}

DLLEXPORT WINBOOL WINAPI IsDialogMessageA (HWND hDlg, LPMSG lpMsg)
{
  return g_imports.user32.IsDialogMessageA(hDlg, lpMsg);
}

DLLEXPORT WINBOOL WINAPI IsDialogMessageW (HWND hDlg, LPMSG lpMsg)
{
  return g_imports.user32.IsDialogMessageW(hDlg, lpMsg);
}

DLLEXPORT WINBOOL WINAPI MapDialogRect (HWND hDlg, LPRECT lpRect)
{
  return g_imports.user32.MapDialogRect(hDlg, lpRect);
}

DLLEXPORT int WINAPI DlgDirListA (HWND hDlg, LPSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT uFileType)
{
  return g_imports.user32.DlgDirListA(hDlg, lpPathSpec, nIDListBox, nIDStaticPath, uFileType);
}

DLLEXPORT int WINAPI DlgDirListW (HWND hDlg, LPWSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT uFileType)
{
  return g_imports.user32.DlgDirListW(hDlg, lpPathSpec, nIDListBox, nIDStaticPath, uFileType);
}

DLLEXPORT WINBOOL WINAPI DlgDirSelectExA (HWND hwndDlg, LPSTR lpString, int chCount, int idListBox)
{
  return g_imports.user32.DlgDirSelectExA(hwndDlg, lpString, chCount, idListBox);
}

DLLEXPORT WINBOOL WINAPI DlgDirSelectExW (HWND hwndDlg, LPWSTR lpString, int chCount, int idListBox)
{
  return g_imports.user32.DlgDirSelectExW(hwndDlg, lpString, chCount, idListBox);
}

DLLEXPORT int WINAPI DlgDirListComboBoxA (HWND hDlg, LPSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT uFiletype)
{
  return g_imports.user32.DlgDirListComboBoxA(hDlg, lpPathSpec, nIDComboBox, nIDStaticPath, uFiletype);
}

DLLEXPORT int WINAPI DlgDirListComboBoxW (HWND hDlg, LPWSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT uFiletype)
{
  return g_imports.user32.DlgDirListComboBoxW(hDlg, lpPathSpec, nIDComboBox, nIDStaticPath, uFiletype);
}

DLLEXPORT WINBOOL WINAPI DlgDirSelectComboBoxExA (HWND hwndDlg, LPSTR lpString, int cchOut, int idComboBox)
{
  return g_imports.user32.DlgDirSelectComboBoxExA(hwndDlg, lpString, cchOut, idComboBox);
}

DLLEXPORT WINBOOL WINAPI DlgDirSelectComboBoxExW (HWND hwndDlg, LPWSTR lpString, int cchOut, int idComboBox)
{
  return g_imports.user32.DlgDirSelectComboBoxExW(hwndDlg, lpString, cchOut, idComboBox);
}

DLLEXPORT int WINAPI SetScrollInfo (HWND hwnd, int nBar, LPCSCROLLINFO lpsi, WINBOOL redraw)
{
  return g_imports.user32.SetScrollInfo(hwnd, nBar, lpsi, redraw);
}

DLLEXPORT WINBOOL WINAPI GetScrollInfo (HWND hwnd, int nBar, LPSCROLLINFO lpsi)
{
  return g_imports.user32.GetScrollInfo(hwnd, nBar, lpsi);
}

DLLEXPORT LRESULT WINAPI DefFrameProcA (HWND hWnd, HWND hWndMDIClient, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.DefFrameProcA(hWnd, hWndMDIClient, uMsg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI DefFrameProcW (HWND hWnd, HWND hWndMDIClient, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.DefFrameProcW(hWnd, hWndMDIClient, uMsg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI DefMDIChildProcA (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.DefMDIChildProcA(hWnd, uMsg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI DefMDIChildProcW (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  return g_imports.user32.DefMDIChildProcW(hWnd, uMsg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI TranslateMDISysAccel (HWND hWndClient, LPMSG lpMsg)
{
  return g_imports.user32.TranslateMDISysAccel(hWndClient, lpMsg);
}

DLLEXPORT UINT WINAPI ArrangeIconicWindows (HWND hWnd)
{
  return g_imports.user32.ArrangeIconicWindows(hWnd);
}

DLLEXPORT HWND WINAPI CreateMDIWindowA (LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInstance, LPARAM lParam)
{
  return g_imports.user32.CreateMDIWindowA(lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hInstance, lParam);
}

DLLEXPORT HWND WINAPI CreateMDIWindowW (LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInstance, LPARAM lParam)
{
  return g_imports.user32.CreateMDIWindowW(lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hInstance, lParam);
}

DLLEXPORT WORD WINAPI TileWindows (HWND hwndParent, UINT wHow, CONST RECT * lpRect, UINT cKids, const HWND * lpKids)
{
  return g_imports.user32.TileWindows(hwndParent, wHow, lpRect, cKids, lpKids);
}

DLLEXPORT WORD WINAPI CascadeWindows (HWND hwndParent, UINT wHow, CONST RECT * lpRect, UINT cKids, const HWND * lpKids)
{
  return g_imports.user32.CascadeWindows(hwndParent, wHow, lpRect, cKids, lpKids);
}

DLLEXPORT WINBOOL WINAPI WinHelpA (HWND hWndMain, LPCSTR lpszHelp, UINT uCommand, ULONG_PTR dwData)
{
  return g_imports.user32.WinHelpA(hWndMain, lpszHelp, uCommand, dwData);
}

DLLEXPORT WINBOOL WINAPI WinHelpW (HWND hWndMain, LPCWSTR lpszHelp, UINT uCommand, ULONG_PTR dwData)
{
  return g_imports.user32.WinHelpW(hWndMain, lpszHelp, uCommand, dwData);
}

DLLEXPORT DWORD WINAPI GetGuiResources (HANDLE hProcess, DWORD uiFlags)
{
  return g_imports.user32.GetGuiResources(hProcess, uiFlags);
}

DLLEXPORT LONG WINAPI ChangeDisplaySettingsA (LPDEVMODEA lpDevMode, DWORD dwFlags)
{
  return g_imports.user32.ChangeDisplaySettingsA(lpDevMode, dwFlags);
}

DLLEXPORT LONG WINAPI ChangeDisplaySettingsW (LPDEVMODEW lpDevMode, DWORD dwFlags)
{
  return g_imports.user32.ChangeDisplaySettingsW(lpDevMode, dwFlags);
}

DLLEXPORT LONG WINAPI ChangeDisplaySettingsExA (LPCSTR lpszDeviceName, LPDEVMODEA lpDevMode, HWND hwnd, DWORD dwflags, LPVOID lParam)
{
  return g_imports.user32.ChangeDisplaySettingsExA(lpszDeviceName, lpDevMode, hwnd, dwflags, lParam);
}

DLLEXPORT LONG WINAPI ChangeDisplaySettingsExW (LPCWSTR lpszDeviceName, LPDEVMODEW lpDevMode, HWND hwnd, DWORD dwflags, LPVOID lParam)
{
  return g_imports.user32.ChangeDisplaySettingsExW(lpszDeviceName, lpDevMode, hwnd, dwflags, lParam);
}

DLLEXPORT WINBOOL WINAPI EnumDisplaySettingsA (LPCSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEA lpDevMode)
{
  return g_imports.user32.EnumDisplaySettingsA(lpszDeviceName, iModeNum, lpDevMode);
}

DLLEXPORT WINBOOL WINAPI EnumDisplaySettingsW (LPCWSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEW lpDevMode)
{
  return g_imports.user32.EnumDisplaySettingsW(lpszDeviceName, iModeNum, lpDevMode);
}

DLLEXPORT WINBOOL WINAPI EnumDisplaySettingsExA (LPCSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEA lpDevMode, DWORD dwFlags)
{
  return g_imports.user32.EnumDisplaySettingsExA(lpszDeviceName, iModeNum, lpDevMode, dwFlags);
}

DLLEXPORT WINBOOL WINAPI EnumDisplaySettingsExW (LPCWSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEW lpDevMode, DWORD dwFlags)
{
  return g_imports.user32.EnumDisplaySettingsExW(lpszDeviceName, iModeNum, lpDevMode, dwFlags);
}

DLLEXPORT WINBOOL WINAPI EnumDisplayDevicesA (LPCSTR lpDevice, DWORD iDevNum, PDISPLAY_DEVICEA lpDisplayDevice, DWORD dwFlags)
{
  return g_imports.user32.EnumDisplayDevicesA(lpDevice, iDevNum, lpDisplayDevice, dwFlags);
}

DLLEXPORT WINBOOL WINAPI EnumDisplayDevicesW (LPCWSTR lpDevice, DWORD iDevNum, PDISPLAY_DEVICEW lpDisplayDevice, DWORD dwFlags)
{
  return g_imports.user32.EnumDisplayDevicesW(lpDevice, iDevNum, lpDisplayDevice, dwFlags);
}

DLLEXPORT LONG WINAPI GetDisplayConfigBufferSizes (UINT32 flags, UINT32 * numPathArrayElements, UINT32 * numModeInfoArrayElements)
{
  return g_imports.user32.GetDisplayConfigBufferSizes(flags, numPathArrayElements, numModeInfoArrayElements);
}

DLLEXPORT LONG WINAPI SetDisplayConfig (UINT32 numPathArrayElements, DISPLAYCONFIG_PATH_INFO * pathArray, UINT32 numModeInfoArrayElements, DISPLAYCONFIG_MODE_INFO * modeInfoArray, UINT32 flags)
{
  return g_imports.user32.SetDisplayConfig(numPathArrayElements, pathArray, numModeInfoArrayElements, modeInfoArray, flags);
}

DLLEXPORT LONG WINAPI QueryDisplayConfig (UINT32 flags, UINT32 * numPathArrayElements, DISPLAYCONFIG_PATH_INFO * pathArray, UINT32 * numModeInfoArrayElements, DISPLAYCONFIG_MODE_INFO * modeInfoArray, DISPLAYCONFIG_TOPOLOGY_ID * currentTopologyId)
{
  return g_imports.user32.QueryDisplayConfig(flags, numPathArrayElements, pathArray, numModeInfoArrayElements, modeInfoArray, currentTopologyId);
}

DLLEXPORT LONG WINAPI DisplayConfigGetDeviceInfo (DISPLAYCONFIG_DEVICE_INFO_HEADER * requestPacket)
{
  return g_imports.user32.DisplayConfigGetDeviceInfo(requestPacket);
}

DLLEXPORT LONG WINAPI DisplayConfigSetDeviceInfo (DISPLAYCONFIG_DEVICE_INFO_HEADER * setPacket)
{
  return g_imports.user32.DisplayConfigSetDeviceInfo(setPacket);
}

DLLEXPORT WINBOOL WINAPI SystemParametersInfoA (UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
  return g_imports.user32.SystemParametersInfoA(uiAction, uiParam, pvParam, fWinIni);
}

DLLEXPORT WINBOOL WINAPI SystemParametersInfoW (UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
  return g_imports.user32.SystemParametersInfoW(uiAction, uiParam, pvParam, fWinIni);
}

DLLEXPORT VOID WINAPI SetDebugErrorLevel (DWORD dwLevel)
{
  g_imports.user32.SetDebugErrorLevel(dwLevel);
}

DLLEXPORT VOID WINAPI SetLastErrorEx (DWORD dwErrCode, DWORD dwType)
{
  g_imports.user32.SetLastErrorEx(dwErrCode, dwType);
}

DLLEXPORT int WINAPI InternalGetWindowText (HWND hWnd, LPWSTR pString, int cchMaxCount)
{
  return g_imports.user32.InternalGetWindowText(hWnd, pString, cchMaxCount);
}

DLLEXPORT WINBOOL WINAPI CancelShutdown (VOID)
{
  return g_imports.user32.CancelShutdown();
}

DLLEXPORT HMONITOR WINAPI MonitorFromPoint (POINT pt, DWORD dwFlags)
{
  return g_imports.user32.MonitorFromPoint(pt, dwFlags);
}

DLLEXPORT HMONITOR WINAPI MonitorFromRect (LPCRECT lprc, DWORD dwFlags)
{
  return g_imports.user32.MonitorFromRect(lprc, dwFlags);
}

DLLEXPORT HMONITOR WINAPI MonitorFromWindow (HWND hwnd, DWORD dwFlags)
{
  return g_imports.user32.MonitorFromWindow(hwnd, dwFlags);
}

#ifdef WINNT
DLLEXPORT WINBOOL WINAPI EndTask (HWND hWnd, WINBOOL fShutDown, WINBOOL fForce)
{
  return g_imports.user32.EndTask(hWnd, fShutDown, fForce);
}
#endif

DLLEXPORT WINBOOL WINAPI SoundSentry (VOID)
{
  return g_imports.user32.SoundSentry();
}

DLLEXPORT WINBOOL WINAPI GetMonitorInfoA (HMONITOR hMonitor, LPMONITORINFO lpmi)
{
  return g_imports.user32.GetMonitorInfoA(hMonitor, lpmi);
}

DLLEXPORT WINBOOL WINAPI GetMonitorInfoW (HMONITOR hMonitor, LPMONITORINFO lpmi)
{
  return g_imports.user32.GetMonitorInfoW(hMonitor, lpmi);
}

DLLEXPORT WINBOOL WINAPI EnumDisplayMonitors (HDC hdc, LPCRECT lprcClip, MONITORENUMPROC lpfnEnum, LPARAM dwData)
{
  return g_imports.user32.EnumDisplayMonitors(hdc, lprcClip, lpfnEnum, dwData);
}

DLLEXPORT VOID WINAPI NotifyWinEvent (DWORD event, HWND hwnd, LONG idObject, LONG idChild)
{
  g_imports.user32.NotifyWinEvent(event, hwnd, idObject, idChild);
}

DLLEXPORT HWINEVENTHOOK WINAPI SetWinEventHook (DWORD eventMin, DWORD eventMax, HMODULE hmodWinEventProc, WINEVENTPROC pfnWinEventProc, DWORD idProcess, DWORD idThread, DWORD dwFlags)
{
  return g_imports.user32.SetWinEventHook(eventMin, eventMax, hmodWinEventProc, pfnWinEventProc, idProcess, idThread, dwFlags);
}

DLLEXPORT WINBOOL WINAPI IsWinEventHookInstalled (DWORD event)
{
  return g_imports.user32.IsWinEventHookInstalled(event);
}

DLLEXPORT WINBOOL WINAPI UnhookWinEvent (HWINEVENTHOOK hWinEventHook)
{
  return g_imports.user32.UnhookWinEvent(hWinEventHook);
}

DLLEXPORT WINBOOL WINAPI GetGUIThreadInfo (DWORD idThread, PGUITHREADINFO pgui)
{
  return g_imports.user32.GetGUIThreadInfo(idThread, pgui);
}

DLLEXPORT WINBOOL WINAPI BlockInput (WINBOOL fBlockIt)
{
  return g_imports.user32.BlockInput(fBlockIt);
}

DLLEXPORT UINT WINAPI GetWindowModuleFileNameA (HWND hwnd, LPSTR pszFileName, UINT cchFileNameMax)
{
  return g_imports.user32.GetWindowModuleFileNameA(hwnd, pszFileName, cchFileNameMax);
}

DLLEXPORT UINT WINAPI GetWindowModuleFileNameW (HWND hwnd, LPWSTR pszFileName, UINT cchFileNameMax)
{
  return g_imports.user32.GetWindowModuleFileNameW(hwnd, pszFileName, cchFileNameMax);
}

DLLEXPORT WINBOOL WINAPI SetProcessDPIAware (VOID)
{
  return g_imports.user32.SetProcessDPIAware();
}

DLLEXPORT WINBOOL WINAPI IsProcessDPIAware (VOID)
{
  return g_imports.user32.IsProcessDPIAware();
}

DLLEXPORT WINBOOL WINAPI GetCursorInfo (PCURSORINFO pci)
{
  return g_imports.user32.GetCursorInfo(pci);
}

DLLEXPORT WINBOOL WINAPI GetWindowInfo (HWND hwnd, PWINDOWINFO pwi)
{
  return g_imports.user32.GetWindowInfo(hwnd, pwi);
}

DLLEXPORT WINBOOL WINAPI GetTitleBarInfo (HWND hwnd, PTITLEBARINFO pti)
{
  return g_imports.user32.GetTitleBarInfo(hwnd, pti);
}

DLLEXPORT WINBOOL WINAPI GetMenuBarInfo (HWND hwnd, LONG idObject, LONG idItem, PMENUBARINFO pmbi)
{
  return g_imports.user32.GetMenuBarInfo(hwnd, idObject, idItem, pmbi);
}

DLLEXPORT WINBOOL WINAPI GetScrollBarInfo (HWND hwnd, LONG idObject, PSCROLLBARINFO psbi)
{
  return g_imports.user32.GetScrollBarInfo(hwnd, idObject, psbi);
}

DLLEXPORT WINBOOL WINAPI GetComboBoxInfo (HWND hwndCombo, PCOMBOBOXINFO pcbi)
{
  return g_imports.user32.GetComboBoxInfo(hwndCombo, pcbi);
}

DLLEXPORT HWND WINAPI GetAncestor (HWND hwnd, UINT gaFlags)
{
  return g_imports.user32.GetAncestor(hwnd, gaFlags);
}

DLLEXPORT HWND WINAPI RealChildWindowFromPoint (HWND hwndParent, POINT ptParentClientCoords)
{
  return g_imports.user32.RealChildWindowFromPoint(hwndParent, ptParentClientCoords);
}

DLLEXPORT UINT WINAPI RealGetWindowClassA (HWND hwnd, LPSTR ptszClassName, UINT cchClassNameMax)
{
  return g_imports.user32.RealGetWindowClassA(hwnd, ptszClassName, cchClassNameMax);
}

DLLEXPORT UINT WINAPI RealGetWindowClassW (HWND hwnd, LPWSTR ptszClassName, UINT cchClassNameMax)
{
  return g_imports.user32.RealGetWindowClassW(hwnd, ptszClassName, cchClassNameMax);
}

DLLEXPORT WINBOOL WINAPI GetAltTabInfoA (HWND hwnd, int iItem, PALTTABINFO pati, LPSTR pszItemText, UINT cchItemText)
{
  return g_imports.user32.GetAltTabInfoA(hwnd, iItem, pati, pszItemText, cchItemText);
}

DLLEXPORT WINBOOL WINAPI GetAltTabInfoW (HWND hwnd, int iItem, PALTTABINFO pati, LPWSTR pszItemText, UINT cchItemText)
{
  return g_imports.user32.GetAltTabInfoW(hwnd, iItem, pati, pszItemText, cchItemText);
}

DLLEXPORT DWORD WINAPI GetListBoxInfo (HWND hwnd)
{
  return g_imports.user32.GetListBoxInfo(hwnd);
}

DLLEXPORT WINBOOL WINAPI LockWorkStation (VOID)
{
  return g_imports.user32.LockWorkStation();
}

DLLEXPORT WINBOOL WINAPI UserHandleGrantAccess (HANDLE hUserHandle, HANDLE hJob, WINBOOL bGrant)
{
  return g_imports.user32.UserHandleGrantAccess(hUserHandle, hJob, bGrant);
}

DLLEXPORT UINT WINAPI GetRawInputData (HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
{
  return g_imports.user32.GetRawInputData(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);
}

DLLEXPORT UINT WINAPI GetRawInputDeviceInfoA (HANDLE hDevice, UINT uiCommand, LPVOID pData, PUINT pcbSize)
{
  return g_imports.user32.GetRawInputDeviceInfoA(hDevice, uiCommand, pData, pcbSize);
}

DLLEXPORT UINT WINAPI GetRawInputDeviceInfoW (HANDLE hDevice, UINT uiCommand, LPVOID pData, PUINT pcbSize)
{
  return g_imports.user32.GetRawInputDeviceInfoW(hDevice, uiCommand, pData, pcbSize);
}

DLLEXPORT UINT WINAPI GetRawInputBuffer (PRAWINPUT pData, PUINT pcbSize, UINT cbSizeHeader)
{
  return g_imports.user32.GetRawInputBuffer(pData, pcbSize, cbSizeHeader);
}

DLLEXPORT WINBOOL WINAPI RegisterRawInputDevices (PCRAWINPUTDEVICE pRawInputDevices, UINT uiNumDevices, UINT cbSize)
{
  return g_imports.user32.RegisterRawInputDevices(pRawInputDevices, uiNumDevices, cbSize);
}

DLLEXPORT UINT WINAPI GetRegisteredRawInputDevices (PRAWINPUTDEVICE pRawInputDevices, PUINT puiNumDevices, UINT cbSize)
{
  return g_imports.user32.GetRegisteredRawInputDevices(pRawInputDevices, puiNumDevices, cbSize);
}

DLLEXPORT UINT WINAPI GetRawInputDeviceList (PRAWINPUTDEVICELIST pRawInputDeviceList, PUINT puiNumDevices, UINT cbSize)
{
  return g_imports.user32.GetRawInputDeviceList(pRawInputDeviceList, puiNumDevices, cbSize);
}

DLLEXPORT LRESULT WINAPI DefRawInputProc (PRAWINPUT * paRawInput, INT nInput, UINT cbSizeHeader)
{
  return g_imports.user32.DefRawInputProc(paRawInput, nInput, cbSizeHeader);
}

DLLEXPORT WINBOOL WINAPI GetPointerDevices (UINT32 * deviceCount, POINTER_DEVICE_INFO * pointerDevices)
{
  return g_imports.user32.GetPointerDevices(deviceCount, pointerDevices);
}

DLLEXPORT WINBOOL WINAPI GetPointerDevice (HANDLE device, POINTER_DEVICE_INFO * pointerDevice)
{
  return g_imports.user32.GetPointerDevice(device, pointerDevice);
}

DLLEXPORT WINBOOL WINAPI GetPointerDeviceProperties (HANDLE device, UINT32 * propertyCount, POINTER_DEVICE_PROPERTY * pointerProperties)
{
  return g_imports.user32.GetPointerDeviceProperties(device, propertyCount, pointerProperties);
}

DLLEXPORT WINBOOL WINAPI RegisterPointerDeviceNotifications (HWND window, WINBOOL notifyRange)
{
  return g_imports.user32.RegisterPointerDeviceNotifications(window, notifyRange);
}

DLLEXPORT WINBOOL WINAPI GetPointerDeviceRects (HANDLE device, RECT * pointerDeviceRect, RECT * displayRect)
{
  return g_imports.user32.GetPointerDeviceRects(device, pointerDeviceRect, displayRect);
}

DLLEXPORT WINBOOL WINAPI GetPointerDeviceCursors (HANDLE device, UINT32 * cursorCount, POINTER_DEVICE_CURSOR_INFO * deviceCursors)
{
  return g_imports.user32.GetPointerDeviceCursors(device, cursorCount, deviceCursors);
}

DLLEXPORT WINBOOL WINAPI GetRawPointerDeviceData (UINT32 pointerId, UINT32 historyCount, UINT32 propertiesCount, POINTER_DEVICE_PROPERTY * pProperties, LONG * pValues)
{
  return g_imports.user32.GetRawPointerDeviceData(pointerId, historyCount, propertiesCount, pProperties, pValues);
}

DLLEXPORT WINBOOL WINAPI ChangeWindowMessageFilter (UINT message, DWORD dwFlag)
{
  return g_imports.user32.ChangeWindowMessageFilter(message, dwFlag);
}

DLLEXPORT WINBOOL WINAPI ChangeWindowMessageFilterEx (HWND hwnd, UINT message, DWORD action, PCHANGEFILTERSTRUCT pChangeFilterStruct)
{
  return g_imports.user32.ChangeWindowMessageFilterEx(hwnd, message, action, pChangeFilterStruct);
}

DLLEXPORT WINBOOL WINAPI GetGestureInfo (HGESTUREINFO hGestureInfo, PGESTUREINFO pGestureInfo)
{
  return g_imports.user32.GetGestureInfo(hGestureInfo, pGestureInfo);
}

DLLEXPORT WINBOOL WINAPI GetGestureExtraArgs (HGESTUREINFO hGestureInfo, UINT cbExtraArgs, PBYTE pExtraArgs)
{
  return g_imports.user32.GetGestureExtraArgs(hGestureInfo, cbExtraArgs, pExtraArgs);
}

DLLEXPORT WINBOOL WINAPI CloseGestureInfoHandle (HGESTUREINFO hGestureInfo)
{
  return g_imports.user32.CloseGestureInfoHandle(hGestureInfo);
}

DLLEXPORT WINBOOL WINAPI SetGestureConfig (HWND hwnd, DWORD dwReserved, UINT cIDs, PGESTURECONFIG pGestureConfig, UINT cbSize)
{
  return g_imports.user32.SetGestureConfig(hwnd, dwReserved, cIDs, pGestureConfig, cbSize);
}

DLLEXPORT WINBOOL WINAPI GetGestureConfig (HWND hwnd, DWORD dwReserved, DWORD dwFlags, PUINT pcIDs, PGESTURECONFIG pGestureConfig, UINT cbSize)
{
  return g_imports.user32.GetGestureConfig(hwnd, dwReserved, dwFlags, pcIDs, pGestureConfig, cbSize);
}

DLLEXPORT WINBOOL WINAPI ShutdownBlockReasonCreate (HWND hWnd, LPCWSTR pwszReason)
{
  return g_imports.user32.ShutdownBlockReasonCreate(hWnd, pwszReason);
}

DLLEXPORT WINBOOL WINAPI ShutdownBlockReasonQuery (HWND hWnd, LPWSTR pwszBuff, DWORD * pcchBuff)
{
  return g_imports.user32.ShutdownBlockReasonQuery(hWnd, pwszBuff, pcchBuff);
}

DLLEXPORT WINBOOL WINAPI ShutdownBlockReasonDestroy (HWND hWnd)
{
  return g_imports.user32.ShutdownBlockReasonDestroy(hWnd);
}

DLLEXPORT WINBOOL WINAPI GetCurrentInputMessageSource (INPUT_MESSAGE_SOURCE * inputMessageSource)
{
  return g_imports.user32.GetCurrentInputMessageSource(inputMessageSource);
}

DLLEXPORT WINBOOL WINAPI GetCIMSSM (INPUT_MESSAGE_SOURCE * inputMessageSource)
{
  return g_imports.user32.GetCIMSSM(inputMessageSource);
}

DLLEXPORT WINBOOL WINAPI GetAutoRotationState (PAR_STATE pState)
{
  return g_imports.user32.GetAutoRotationState(pState);
}

DLLEXPORT WINBOOL WINAPI GetDisplayAutoRotationPreferences (ORIENTATION_PREFERENCE * pOrientation)
{
  return g_imports.user32.GetDisplayAutoRotationPreferences(pOrientation);
}

DLLEXPORT WINBOOL WINAPI GetDisplayAutoRotationPreferencesByProcessId (DWORD dwProcessId, ORIENTATION_PREFERENCE * pOrientation, WINBOOL * fRotateScreen)
{
  return g_imports.user32.GetDisplayAutoRotationPreferencesByProcessId(dwProcessId, pOrientation, fRotateScreen);
}

DLLEXPORT WINBOOL WINAPI SetDisplayAutoRotationPreferences (ORIENTATION_PREFERENCE orientation)
{
  return g_imports.user32.SetDisplayAutoRotationPreferences(orientation);
}

DLLEXPORT WINBOOL WINAPI IsImmersiveProcess (HANDLE hProcess)
{
  return g_imports.user32.IsImmersiveProcess(hProcess);
}

DLLEXPORT WINBOOL WINAPI SetProcessRestrictionExemption (WINBOOL fEnableExemption)
{
  return g_imports.user32.SetProcessRestrictionExemption(fEnableExemption);
}

DLLEXPORT WINBOOL WINAPI GetPointerInputTransform (UINT32 pointerId, UINT32 historyCount, UINT32 * inputTransform)
{
  return g_imports.user32.GetPointerInputTransform(pointerId, historyCount, inputTransform);
}

DLLEXPORT WINBOOL WINAPI IsMousePointerEnabled (void)
{
  return g_imports.user32.IsMousePointerEnabled();
} 
