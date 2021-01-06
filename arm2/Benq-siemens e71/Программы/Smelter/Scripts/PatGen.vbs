' Internet Explorer - Сервис - Свойства обозревателя - Безопасность - Другой
' Разрешить операции вставки из сценария - Разрешить

Option Explicit

Dim objIE
Dim s, r, tit, m, i, j

tit = "PatGen"
Set objIE = CreateObject("InternetExplorer.Application")
objIE.Navigate("about:blank")

Do
  Do
    s = objIE.Document.ParentWindow.ClipboardData.getData("Text")
    i = MsgBox(s, vbYesNoCancel, "Clipboard")
    If i = 2 Then WScript.Quit
  Loop While i = 7

  m = Split(s, vbCrLf)
  r = ""
  For i=0 To UBound(m)
    s = Trim(m(i))
    j = InStr(s, "  ")
    If j > 0 Then
      s = Left(s, j-1)
      j = InStr(s, " ")
      If j > 0 Then
        s = Mid(s, j+1)
        s = Replace(s, " ", "")
        j = Len(s)
        If j = 8 And Mid(s, 3, 1) = "F" And (Mid(s, 7, 1) = "E" Or Mid(s, 7, 1) = "F") Then s = "????????"
        s = String(j-2, "?") & Right(s,2)
        r = r & "," & s
      End If
    End If
  Next

  r = InputBox("Pattern", tit, Mid(r, 2))
Loop While r = vbEmpty

objIE.Document.ParentWindow.ClipboardData.setData "Text", r
