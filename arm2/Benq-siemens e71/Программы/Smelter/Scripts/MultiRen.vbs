' MultiRen [file] [template]

Option Explicit

Dim objArgs, objDialog, objFSO
Dim s, t, k, a(1000), b(1000)
Dim pth, ext, f, tit
Dim pri, suf, l

tit = "MultiRen"

Set objArgs = WScript.Arguments
If objArgs.Count >= 1 Then
  s = objArgs(0)
Else
  Set objDialog = CreateObject("UserAccounts.CommonDialog")
  If objDialog.ShowOpen = 0 Then WScript.Quit
  s = objDialog.FileName 
End If

Set objFSO = CreateObject("Scripting.FileSystemObject")
pth = objFSO.GetParentFolderName(s) & "\"
ext = objFSO.GetExtensionName(s)

t = ""
If objArgs.Count >= 2 Then t = objArgs(1): s = "skip"

Do
  If t = "" Then t = objFSO.GetBaseName(pth) & "_##"
  If s <> "skip" Then t = InputBox("Enter the template", tit, t)
  If t = vbEmpty Then WScript.Quit

  pri = Left(t, InStr(t, "#") - 1)
  suf = Mid(t, InStrRev(t, "#") + 1)
  l = Len(t) - Len(pri) - Len(suf)

  k = 0
  s = ""
  For Each f In objFSO.GetFolder(pth).Files
    If objFSO.GetExtensionName(f.Name) = ext Then
      k = k + 1
      a(k) = f.Name
      b(k) = pri & Right("00000000" & k, l) & suf & "." & ext
      s = s  & vbCrLf & a(k) & " ==> " & b(k)
    End If
  Next
  s = "Path: " & pth & vbCrLf & "Files: " & k & vbCrLf & s
  l = MsgBox(s, vbYesNoCancel, tit)
  If l = 2 Then WScript.Quit
Loop While l = 7

For l = 1 To k
  objFSO.MoveFile pth & a(l), pth & b(l)
Next
