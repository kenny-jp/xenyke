XKE_NAMESPACE_BEGIN

glm::mat4 Camera<CameraType2D>::mvpMat(const xke::Vec2u& windowSize, const xke::Vec2f& cameraPos,
                        const Transform& tr)
{
    return projectionMat(windowSize) * viewMat(cameraPos) * modelMat(tr);
}

glm::mat4 Camera<CameraType2D>::modelMat(const Transform& tr)
{
    const auto size = tr.size;
    const auto pos = tr.position;
    const glm::vec3 translation(pos.x + size.x * 0.5, pos.y + size.y * 0.5, 0.f);

    glm::mat4 model {identityMat};
    model = glm::translate(model, translation);
    model = glm::scale(model, glm::vec3(size.x, size.y, 0.f));

    return model;
}

glm::mat4 Camera<CameraType2D>::projectionMat(const xke::Vec2u& size)
{
    return glm::ortho(0.f, static_cast<float>(size.x),
                      static_cast<float>(size.y), 0.f);
}

glm::mat4 Camera<CameraType2D>::viewMat(const xke::Vec2f& pos)
{
    glm::mat4 view {identityMat};
    view = glm::translate(view, glm::vec3(pos.x, pos.y, 1.f));

    return view;
}




glm::mat4 Camera<CameraType3D>::mvpMat(const xke::Vec2u& windowSize, const xke::Vec2f& cameraPos,
                        const xke::Vec2f& pos, const xke::Vec2f size)
{
    return projectionMat(windowSize) * viewMat(cameraPos) * modelMat(pos, size);
}

glm::mat4 Camera<CameraType3D>::modelMat(const xke::Vec2f& pos, const xke::Vec2f size)
{
    glm::mat4 model(1.f);
    model = glm::translate(model, glm::vec3(pos.x, pos.y, 1.f));
    model = glm::scale(model, glm::vec3(size.x, size.y, 1.f));
    model = glm::rotate(model, glm::radians(45.f), glm::vec3(1.f, 1.f, 0.f));
    return model;
}

glm::mat4 Camera<CameraType3D>::projectionMat(const xke::Vec2u& size)
{
    const float aspectRatio {static_cast<float>(size.x) / static_cast<float>(size.y)};
    return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

glm::mat4 Camera<CameraType3D>::viewMat(const xke::Vec2f& pos)
{
    static constexpr glm::vec3 cameraFront = glm::vec3(0.0f, -0.0f, -1.0f);
    static constexpr glm::vec3 cameraUp    = glm::vec3(0.0f, -1.0f,  0.0f);
    glm::vec3 cameraPos(pos.x, pos.y, -64.f);
    return glm::lookAt(cameraPos, cameraPos - cameraFront, cameraUp);
}

XKE_NAMESPACE_END
