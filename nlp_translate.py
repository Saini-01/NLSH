import sys

input_text = ' '.join(sys.argv[1:]).lower()

mappings = {
    "show me the files": "ls",
    "what’s in this folder": "ls",
    "go up a directory": "cd ..",
    "where am i": "pwd",
    "list all": "ls -la",
    "clear the screen": "clear",
    "print": "echo"
}

for phrase, cmd in mappings.items():
    if input_text.startswith(phrase):
        args = input_text[len(phrase):].strip()
        print(f"{cmd} {args}")
        break
else:
    print(input_text)  