
import base64
from openai import OpenAI

# 절대경로 직접 지정
prompt_path = "C:/Users/WONHO/Desktop/mainwindow/build/image_prompt/image_prompt.txt"
output_path = "C:/Users/WONHO/Desktop/mainwindow/build/output_image/image.png"

instructions="실제 사진처럼 현실감 있는 사진을 만들어주세요."

# 1. 텍스트 파일에서 prompt 읽기
print("프롬프트 읽는 중...\n")

with open(prompt_path, "r", encoding="utf-8") as file:
    user_input_prompt = file.read()
    
prompt=user_input_prompt+instructions

print(f"프롬프트 내용:{user_input_prompt}\n")

# 2. GPT 이미지 생성
client = OpenAI(api_key="본인api키")
print("이미지 생성 요청 중...\n")

result = client.images.generate(
    model="gpt-image-1",
    prompt=prompt
)

# 3. 이미지 디코딩
image_base64 = result.data[0].b64_json
image_bytes = base64.b64decode(image_base64)
print("이미지 디코딩 완료\n")

# 4. 이미지 저장
with open(output_path, "wb") as f:
    f.write(image_bytes)

print("이미지 저장 완료!\n")



