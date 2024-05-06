# ifndef XKE_ENG_CAMERA_HPP
# define XKE_ENG_CAMERA_HPP

# include <xenyke/eng/common.hpp>
# include <xenyke/eng/transform.hpp>
# include <xenyke/gl/ext/glm/gtc/matrix_transform.hpp>

XKE_NAMESPACE_BEGIN

template<>
class Camera<CameraType2D>
{
public:
    static glm::mat4 mvpMat(const xke::Vec2u& windowSize, const xke::Vec2f& cameraPos,
                            const Transform& tr);

    static glm::mat4 modelMat(const Transform& tr);
    static glm::mat4 projectionMat(const xke::Vec2u& size);
    static glm::mat4 viewMat(const xke::Vec2f& pos);

    static constexpr glm::mat4 identityMat = glm::mat4(1.f);
};

template<>
class Camera<CameraType3D>
{
public:
    static glm::mat4 mvpMat(const xke::Vec2u& windowSize, const xke::Vec2f& cameraPos,
                            const xke::Vec2f& pos, const xke::Vec2f size);

    static glm::mat4 modelMat(const xke::Vec2f& pos, const xke::Vec2f size);
    static glm::mat4 projectionMat(const xke::Vec2u& size);
    static glm::mat4 viewMat(const xke::Vec2f& pos);
};

XKE_NAMESPACE_END

# include "camera.inl"

# endif //XKE_ENG_CAMERA_HPP
