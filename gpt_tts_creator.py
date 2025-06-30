from pathlib import Path
from openai import OpenAI

client = OpenAI(api_key="본인api키")  
script_path = Path("C:/Users/WONHO/Desktop/mainwindow/build/output_script/output.txt")
speech_file_path = Path("C:/Users/WONHO/Desktop/mainwindow/build/output_script/speech.mp3")

# 1. 스크립트 읽기
with open(script_path, "r", encoding="utf-8") as f:
    script_text = f.read()

print("tts 스크립트 읽는 중, TTS 생성시작\n")

# 2. TTS 요청 및 저장
with client.audio.speech.with_streaming_response.create(
    model="gpt-4o-mini-tts",
    voice="onyx",
    input=script_text
) as response:
    response.stream_to_file(speech_file_path)

print("명상 TTS파일 생성 및 저장 완료:", speech_file_path)
