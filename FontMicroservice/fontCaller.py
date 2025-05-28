import requests
import json

with open("font.json", "r") as f:
    request = json.load(f)

api_key = request.get("apikey")
family = request.get("family")
style = request.get("style", "regular")

print(api_key)
print(family)
print(style)

response = requests.get("https://www.googleapis.com/webfonts/v1/webfonts?key=" + api_key)
fullData = response.json()

for font in fullData["items"]:
        if font["family"] == family:
                fontDone = font["files"].get(style)

stringFont = str(fontDone)

font = requests.get(stringFont)

if font.status_code == 200:
    with open(family + "-" + style + ".ttf", "wb") as f:
        f.write(font.content)
    print("Font file saved successfully!")
else:
    print("Failed to download font:", response.status_code)