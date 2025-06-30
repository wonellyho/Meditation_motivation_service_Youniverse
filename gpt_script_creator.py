import base64
from openai import OpenAI

# 절대경로
diary_path = "C:/Users/WONHO/Desktop/mainwindow/build/diary_input/diary.txt"
image_path = "C:/Users/WONHO/Desktop/mainwindow/build/output_image/image.png"
output_path = "C:/Users/WONHO/Desktop/mainwindow/build/output_script/output.txt"

# 1. 프롬프트 텍스트 읽기
with open(diary_path, "r", encoding="utf-8") as f:
    diary = f.read()
print("일기 읽기 완료!\n")
print(diary)

# 2. 이미지 → base64 인코딩
with open(image_path, "rb") as f:
    image_bytes = f.read()
    image_base64 = base64.b64encode(image_bytes).decode("utf-8")
print("이미지 인코딩 완료!\n")

# 3. GPT에게 요청
client = OpenAI(api_key="본인API키")  # API 키 그대로 유지

response = client.chat.completions.create(
    model="gpt-4o",
    messages=[
        {
            "role": "user",
            "content": [
                {
                    "type": "text",
                    "text": f"""
                        첨부된 이미지는 사용자의 미래 희망 모습이야.
                        너는 신뢰감 있고, 차분하고, 따뜻한 어조의 명상문을 작성해주세요.
                        사용자가 꿈꾸는 이미지 속 인물이 된 것처럼 한국어로 명상문을 작성해줘
                        사용자가 쓴 일기를 참고해서, 사용자의 하루를 위로해주고, 꿈꾸는 모습이 될수있다고 용기와 격려를 주세요.

                        일기 내용: {diary}
                        """
                },
                {
                    "type": "image_url",
                    "image_url": {
                        "url": "data:image/png;base64," + image_base64
                    }
                }
            ]
        }
    ],
    max_tokens=500
)
print("모델 작동 완료\n")

# 4. 결과 저장
script_output = response.choices[0].message.content

with open(output_path, "w", encoding="utf-8") as file:
    file.write(script_output)

print("명상 스크립트(tts대본) 저장 완료!\n")
