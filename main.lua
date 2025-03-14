local simpledraw = require "SimpleDraw"

funtion Draw(dt)
SimpleDraw.Clear(20,20,20)
SimpleDraw.SetBrushColor(255,0,0)
simpledraw.DrawCircle(200,150,28)
SimpleDraw.SetBrushColor(0,255,0)
SimpleDraw.DrawLine(100,500,500,500)
SimpleDraw.SetBrushColor(0,0,255)
SimpleDraw.DrawRect(300,300,100,100)

webRequest("https://uselessfacts.jsph.pl/api/v2/facts/random")

end