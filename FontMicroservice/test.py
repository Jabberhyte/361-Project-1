import json

print("Enter the name of your font: ")
family = input()

print("Enter the style you would like: ")
style = input()

print("Please enter your API key: ")
apiKey = input()

font = {
    "apikey":apiKey,
    "family":family,
    "style":style,
}

with open("font.json", "w") as f:
    json.dump(font, f, indent=4)