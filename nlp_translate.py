import sys
from openai import OpenAI

client = OpenAI(
  api_key="API KEY"
)

completion = client.chat.completions.create(
  model="gpt-4o-mini",
  store=True,
  messages=[
    {"role": "user", "content": "write a haiku about ai"}
  ]
)

print(completion.choices[0].message);

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