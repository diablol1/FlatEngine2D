#include "AnimationPlayer.hpp"

AnimationPlayer::_addToComponentsCreator AnimationPlayer::_componentsCreatorAdder;
std::unordered_map<std::string, std::shared_ptr<Animation>> AnimationPlayer::Animations;

Component* AnimationPlayer::clone() const {
    return new AnimationPlayer(*this);
}

void AnimationPlayer::serialize(json& jsonData) const {
    jsonData["playing"] = playing;
    jsonData["animation"] = currentAnimation;
    jsonData["frame"] = currentFrame;
}

void AnimationPlayer::deserialize(const json& jsonData) {
    playing = jsonData["playing"];
    currentAnimation = jsonData["animation"];
    currentFrame = jsonData["frame"];

    if (playing)
        loadAnimationIfNotLoaded(currentAnimation);
}

void AnimationPlayer::update(float deltaTime) {
    if (playing) {
        if (timeSinceAnimationStart.getElapsedTime().asSeconds()
            >= Animations[currentAnimation]->getFrame(currentFrame).getStartTime()) {
            currentFrame++;
            entity->getComponent<Sprite>().setTextureRect(Animations[currentAnimation]->getFrame(currentFrame).getLocation());
        }
        if (currentFrame == Animations[currentAnimation]->getNumberOfFrames() - 1) {
            if (Animations[currentAnimation]->isLooped()) {
                play(currentAnimation);
            } else {
                playing = false;
            }
        }
    }
}

void AnimationPlayer::setSpriteSheet(const std::string& filename) {
    entity->getComponent<Sprite>().setTexture(filename);
}

void AnimationPlayer::play(const std::string& filename) {
    loadAnimationIfNotLoaded(filename);

    currentAnimation = filename;
    currentFrame = 0;
    playing = true;
    timeSinceAnimationStart.restart();
}

void AnimationPlayer::stop() {
    playing = false;
}

void AnimationPlayer::loadAnimationIfNotLoaded(const std::string& filename) {
    if (!Animations.count(filename)) {
        Animations.emplace(filename, std::make_shared<Animation>(filename));
    }
}