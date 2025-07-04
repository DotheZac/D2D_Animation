#include "pch.h"
#include "AnimationClip.h"
#include "AsepriteParser.h"
#include "AssetManager.h"

void AssetManager::LoadTexture(sample::D2DRenderer* renderer, std::wstring keyWide, const std::filesystem::path& fullPath)
{
    if (!renderer) return;

    ID2D1Bitmap1* outBitmap = nullptr;

    //outBitmap에 사진이 저장됨
    renderer->CreateBitmapFromFile(fullPath.c_str(), outBitmap);

    if (outBitmap)
    {
        Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap;
        bitmap.Attach(outBitmap); // 참조 관리 시작

        m_textures[keyWide] = bitmap;
    }
}

void AssetManager::LoadAseprite(sample::D2DRenderer* renderer, std::wstring keyWide, const std::filesystem::path& fullPath)
{
    AnimationClips clips = AsepriteParser::Load(fullPath);

    std::filesystem::path texturePath = keyWide;
    texturePath += ".png";

    LoadTexture(renderer, keyWide, texturePath);

    if (!clips.empty())
    {
        auto bitmap = m_textures[keyWide];
        for (auto& clip : clips)
        {               
            clip.second.SetBitmap(bitmap);
        }
        m_clipsMap[keyWide] = std::move(clips);
    }
}

AnimationClips& AssetManager::GetClips(std::wstring selectedAssetKey)
{
    return m_clipsMap[selectedAssetKey];
}

ID2D1Bitmap1* AssetManager::GetTexture(std::wstring selectedAssetKey)
{
    return m_textures[selectedAssetKey].Get();
}




