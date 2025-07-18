import sys, platform, os
from openai import OpenAI
from dotenv import load_dotenv

load_dotenv()

client = OpenAI(
    base_url="https://openrouter.ai/api/v1",
    api_key=os.getenv('KEY'),
)

input_text = " ".join(sys.argv[1:]).lower()

mappings = {
    "show me the files": "ls",
    "what’s in this folder": "ls",
    "go up a directory": "cd ..",
    "where am i": "pwd",
    "list all": "ls -la",
    "clear the screen": "clear",
    "print": "echo",
}

def get_os_type():
    os_name = platform.system()
    if os_name == "Windows":
        return "Windows"
    elif os_name == "Darwin": 
        return "macOS"
    elif os_name == "Linux":
        return "Linux"

if input_text.startswith("ai>"):
    current_os = get_os_type()
    completion = client.chat.completions.create(
        extra_body={},
        model="deepseek/deepseek-r1:free",
        messages=[
            {"role": "system", "content": f"You are a helpful assistant that returns only terminal commands. Respond only with a valid terminal command that matches the user's request. The user's operating system is: {current_os}"},
            {"role": "user", "content": "Return the terminal command to: " + input_text}
        ],
    )
    print("echo " + completion.choices[0].message.content.replace('\n', "").split('```bash')[1].split('```')[0].strip())
else:
    for phrase, cmd in mappings.items():
        if input_text.startswith(phrase):
            args = input_text[len(phrase) :].strip()
            print(f"{cmd} {args}")
            break
    else:
        print(input_text)
