# A demo plugin for Microsoft Outlook (NOT Outlook Express)
#
# This addin simply adds a new button to the main Outlook toolbar,
# and displays a message box when clicked.  Thus, it demonstrates
# how to plug in to Outlook itself, and hook outlook events.
#
# To register the addin, simply execute:
#   outlookAddin.py
# This will install the COM server, and write the necessary
# AddIn key to Outlook
#
# To unregister completely:
#   outlookAddin.py --unregister
#
# To debug, execute:
#   outlookAddin.py --debug
#
# Then open Pythonwin, and select "Tools->Trace Collector Debugging Tool"
# Restart Outlook, and you should see some output generated.
#
# NOTE: If the AddIn fails with an error, Outlook will re-register
# the addin to not automatically load next time Outlook starts.  To
# correct this, simply re-register the addin (see above)

from win32com import universal
from win32com.server.exception import COMException
from win32com.client import gencache, DispatchWithEvents
import winerror
import pythoncom
from win32com.client import constants
import sys

# Support for COM objects we use.
gencache.EnsureModule('{00062FFF-0000-0000-C000-000000000046}', 0, 9, 0, bForDemand=True) # Outlook 9
gencache.EnsureModule('{2DF8D04C-5BFA-101B-BDE5-00AA0044DE52}', 0, 2, 1, bForDemand=True) # Office 9

# The TLB defiining the interfaces we implement
universal.RegisterInterfaces('{AC0714F2-3D04-11D1-AE7D-00A0C90F26F4}', 0, 1, 0, ["_IDTExtensibility2"])

class ButtonEvent:
    def OnClick(self, button, cancel):
        import win32ui # Possible, but not necessary, to use a Pythonwin GUI
        win32ui.MessageBox("Hello from Python")
        return cancel

class OutlookAddin:
    _com_interfaces_ = ['_IDTExtensibility2']
    _public_methods_ = []
    _reg_clsctx_ = pythoncom.CLSCTX_INPROC_SERVER
    _reg_clsid_ = "{0F47D9F3-598B-4d24-B7E3-92AC15ED27E2}"
    _reg_progid_ = "Python.Test.OutlookAddin"
    _reg_policy_spec_ = "win32com.server.policy.EventHandlerPolicy"
    def OnConnection(self, application, connectMode, addin, custom):
        print "OnConnection", application, connectMode, addin, custom
        bars = application.ActiveExplorer().CommandBars
        toolbar = bars.Item("Standard")
        item = toolbar.Controls.Add(Type=constants.msoControlButton, Temporary=True)
        # Hook events for the item
        item = self.toolbarButton = DispatchWithEvents(item, ButtonEvent)
        item.Caption="Python"
        item.TooltipText = "Click for Python"
        item.Enabled = True

        # And now, for the sake of demonstration, setup a hook for all new messages
        print "Session is", application.Session
        inbox = application.Session.GetDefaultFolder(constants.olFolderInbox)
        print "inbox is", inbox
        # sob - can't really make MAPI events work :(  Must be a typelib dependency we don't handle.
        #inbox = DispatchWithEvents(inbox, FolderEvent)

    def OnDisconnection(self, mode, custom):
        print "OnDisconnection"
    def OnAddInsUpdate(self, custom):
        print "OnAddInsUpdate", custom
    def OnStartupComplete(self, custom):
        print "OnStartupComplete", custom
    def OnBeginShutdown(self, custom):
        print "OnBeginShutdown", custom

def RegisterAddin(klass):
    import _winreg
    key = _winreg.CreateKey(_winreg.HKEY_CURRENT_USER, "Software\\Microsoft\\Office\\Outlook\\Addins")
    subkey = _winreg.CreateKey(key, klass._reg_progid_)
    _winreg.SetValueEx(subkey, "CommandLineSafe", 0, _winreg.REG_DWORD, 0)
    _winreg.SetValueEx(subkey, "LoadBehavior", 0, _winreg.REG_DWORD, 3)
    _winreg.SetValueEx(subkey, "Description", 0, _winreg.REG_SZ, klass._reg_progid_)
    _winreg.SetValueEx(subkey, "FriendlyName", 0, _winreg.REG_SZ, klass._reg_progid_)

def UnregisterAddin(klass):
    import _winreg
    try:
        _winreg.DeleteKey(_winreg.HKEY_CURRENT_USER, "Software\\Microsoft\\Office\\Outlook\\Addins\\" + klass._reg_progid_)
    except WindowsError:
        pass

if __name__ == '__main__':
    import win32com.server.register
    win32com.server.register.UseCommandLine(OutlookAddin)
    if "--unregister" in sys.argv:
        UnregisterAddin(OutlookAddin)
    else:
        RegisterAddin(OutlookAddin)
