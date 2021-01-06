' dos2win [infile] [oufile]

Option Explicit

Dim objArgs, objDialog, objFSO, objInFile, objOutFile
Dim s, r, u, i, j, t(255)

Set objArgs = WScript.Arguments
If objArgs.Count >= 1 Then
  s = objArgs(0)
Else
  Set objDialog = CreateObject("UserAccounts.CommonDialog")
  If objDialog.ShowOpen = 0 Then WScript.Quit
  s = objDialog.FileName
End If
u = s
If objArgs.Count >= 2 Then u = objArgs(1)

Set objFSO = CreateObject("Scripting.FileSystemObject")
Set objInFile  = objFSO.OpenTextFile(s)
Set objOutFile = objFSO.OpenTextFile(u & ".d2w", 2, True, 0)

For i=0 To 255
  j = 0
  If &h80 <= i And i <= &hAF Then j = &h40
  If &hE0 <= i And i <= &hEF Then j = &h10
  t(i) = i + j
Next
t(&hF0) = &hA8
t(&hF1) = &hB8
t(&hFC) = &hB9

Do Until objInFile.AtEndOfStream
  s = objInFile.ReadLine
  r = ""
  For i=1 To Len(s)
    r = r & Chr(t(Asc(Mid(s,i,1))))
  Next
  objOutFile.WriteLine r
Loop
objInFile.Close
objOutFile.Close

If objFSO.FileExists(u) Then objFSO.DeleteFile(u)
objFSO.MoveFile u & ".d2w", u
