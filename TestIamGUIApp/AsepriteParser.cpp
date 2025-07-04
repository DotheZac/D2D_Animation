#include "pch.h"
#include <fstream>
#include "json.hpp"
#include "AsepriteParser.h"

AnimationClips AsepriteParser::Load(const std::filesystem::path& jsonPath)
{
    // 1) JSON �ε��ϼ���.
    AnimationClips outData;

    std::ifstream ifs(jsonPath);

    if (!ifs.is_open())
    {
        std::cerr << "������ �� �� ����\n";
        return outData;
    }

    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    auto parsed = nlohmann::json::parse(content, nullptr, false);  // ������ ���� 'false'�� ���� ��Ȱ��ȭ

    if (parsed.is_discarded())
    {
        std::cerr << "JSON �Ľ� ����: ��ȿ���� ���� �����Դϴ�.\n";
        return outData;
    }

    const auto& root = parsed;

    // 2) �±׺���  AnimationClips �����մϴ�.
    AnimationClips clips;

    auto& framesNode = root["frames"];
    auto& tagsNode = root["meta"]["frameTags"];

    std::vector<Frame> frames;

    if (framesNode.is_object())
    {
        for (auto it = framesNode.begin(); it != framesNode.end(); ++it)
        {
            const auto& f = it.value();
            Frame ff;
            ff.duration = f["duration"] / 1000.f;
            ff.srcRect.left = f["frame"]["x"];
            ff.srcRect.right = ff.srcRect.left + f["frame"]["w"];
            ff.srcRect.top = f["frame"]["y"];
            ff.srcRect.bottom = ff.srcRect.top + f["frame"]["h"];
            frames.push_back(ff);
        }
    }
    if (framesNode.is_array())
    {
        for (auto it = framesNode.begin(); it != framesNode.end(); ++it)
        {
            const auto& f = it.value();
            Frame ff;
            ff.duration = f["duration"] / 1000.f;
            ff.srcRect.left = f["frame"]["x"];
            ff.srcRect.right = ff.srcRect.left + f["frame"]["w"];
            ff.srcRect.top = f["frame"]["y"];
            ff.srcRect.bottom = ff.srcRect.top + f["frame"]["h"];
            
            frames.push_back(ff);
        }
    }

    if (tagsNode.is_object())
    {
        for (auto it = tagsNode.begin(); it != tagsNode.end(); ++it)
        {
            const auto& a = it.value();
            AnimationClip aa;
            std::string name = a["name"];
            int first = a["from"];
            int last = a["to"];
            std::string dir = a["direction"];
            if (dir == "forward")
            {
                for (int i = first; i <= last; i++)
                {
                    aa.AddFrame(frames[i]);
                }
            }
            else if (dir == "reverse")
            {
                for (int i = last; i >= first; i--)
                {
                    aa.AddFrame(frames[i]);
                }
            }
            clips.emplace_back(name, std::move(aa));
        }
    }

    if (tagsNode.is_array())
    {
        for (auto it = tagsNode.begin(); it != tagsNode.end(); ++it)
        {
            const auto& a = it.value();
            AnimationClip aa;
            std::string name = a["name"];
            int first = a["from"];
            int last = a["to"];
            std::string dir = a["direction"];
            if (dir == "forward")
            {
                for (int i = first; i <= last; i++)
                {
                    aa.AddFrame(frames[i]);
                }
            }
            else if (dir == "reverse")
            {
                for (int i = last; i >= first; i--)
                {
                    aa.AddFrame(frames[i]);
                }
            }
            clips.emplace_back(name, std::move(aa));
        }
    }

    return clips;
}
