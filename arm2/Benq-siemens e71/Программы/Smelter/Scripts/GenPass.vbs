Option Explicit
Dim t, a, n, s, l, i, d

t = "GenPass"
a = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
n = Len(a)

s = InputBox("Enter the length of password", t, 8)
If Not IsNumeric(s) Then WScript.Quit
l = CInt(s)
If l < 1 Then WScript.Quit

Do
  Randomize
  s = ""
  For i = 1 To l
    d = Now()
    While DateDiff("s", d, Now()) < 1
      Rnd()
    Wend
    s = s & Mid(a, n*Rnd()+1, 1)
  Next
  s = InputBox("Password is " & s & vbCrLf & vbCrLf &  "(Ok - repeat)", t, s)
Loop While s <> vbEmpty
