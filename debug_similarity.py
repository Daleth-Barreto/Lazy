import requests
import numpy as np

def get_embedding(text):
    url = "http://localhost:11434/api/embeddings"
    data = {"model": "qwen2:0.5b", "prompt": text}
    response = requests.post(url, json=data)
    if response.status_code == 200:
        return np.array(response.json()["embedding"])
    else:
        print(f"Error: {response.text}")
        return None

def cosine_similarity(v1, v2):
    dot_product = np.dot(v1, v2)
    norm1 = np.linalg.norm(v1)
    norm2 = np.linalg.norm(v2)
    return dot_product / (norm1 * norm2)

v1 = get_embedding("start game")
v2 = get_embedding("end playing")

if v1 is not None and v2 is not None:
    sim = cosine_similarity(v1, v2)
    print(f"Cosine Similarity: {sim}")
    normalized_sim = (sim + 1.0) / 2.0
    print(f"Normalized (0-1): {normalized_sim}")
