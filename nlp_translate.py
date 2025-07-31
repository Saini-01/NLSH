import sys, platform, os
from openai import OpenAI
from dotenv import load_dotenv

load_dotenv()

client = OpenAI(
    base_url="https://openrouter.ai/api/v1",
    api_key=os.getenv("OPENROUTER_KEY"),
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
    "who am i": "whoami",
    "show hidden files": "ls -la",
    "check disk space": "df -h",
    "show processes": "ps aux",
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
    command_text = input_text[3:].strip()
    for phrase, cmd in mappings.items():
        if command_text.startswith(phrase):
            args = command_text[len(phrase):].strip()
            print(f"{cmd} {args}")
            break
    else:
        current_os = get_os_type()
        completion = client.chat.completions.create(
            extra_body={},
            model="deepseek/deepseek-r1:free",
            messages=[
                {"role": "system", "content": f"You are a helpful assistant that returns only terminal commands. Respond only with a valid terminal command that matches the user's request. The user's operating system is: {current_os}"},
                {"role": "user", "content": f"Return ONLY the terminal command to: {command_text}. Do not wrap it in markdown or backticks."}
            ],
        )
        print(completion.choices[0].message.content.strip())
else:
    print(input_text)
