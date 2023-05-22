# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)

# Declares and names the project.

project("sumobomber")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.


include_directories(engine/)


add_library( # Sets the name of the library.
        sumobomber

        # Sets the library as a shared library.
        SHARED
        #game object
        engine/GameObject/GameObject.cpp
        engine/GameObject/Instance.cpp
        #shapes
        engine/Shape/Rectangle.cpp
        #resource
        engine/Resource/Image.cpp
        engine/Resource/Resource.cpp
        engine/Resource/Sprite.cpp
        engine/Resource/Material.cpp
        engine/Resource/Font.cpp
        engine/Resource/Scene.cpp
        #rendering
        engine/Renderer/Renderer.cpp
        engine/Renderer/Texture.cpp
        engine/Renderer/Screen.cpp
        engine/Renderer/Camera.cpp
        engine/Renderer/Context.cpp
        engine/Renderer/Color.cpp
        engine/Renderer/Graphics.cpp
        engine/Renderer/Vertex.cpp
        engine/Renderer/Quad.cpp
        engine/Renderer/VertexBufferObject.cpp
        #math
        engine/Math/Random.cpp
        #input
        engine/InputEvent/InputEvent.cpp
        #tween
        engine/Interpolation/Interpolate.cpp
        #particles
        engine/Particles/ParticleEmitter.cpp
        #app
        engine/Application/Application.cpp
        #game objects
        Objects/Sumo/Sumo.cpp
        Objects/Terrain/Terrain.cpp
        Objects/CameraController/CameraController.cpp
        Objects/Ball/Ball.cpp
        Objects/Ball/BallSolo/BallSolo.cpp
        Objects/Ball/BallVs/BallVs.cpp
        #ui
        Objects/UI/Button/Button.cpp
        Objects/UI/Button/ButtonParticle.cpp
        Objects/UI/TitleScreen/TitleScreen.cpp
        Objects/UI/TransitionManager/TransitionManager.cpp
        Objects/UI/SplashScreen/SplashScreen.cpp
        Objects/UI/HudVs/HudVs.cpp
        Objects/UI/Pause/PauseMenu.cpp
        #score
        Objects/System/ScoreManager/ScoreManager.cpp

        #audio
        AudioEngine/PlaySound.cpp

        # Provides a relative path to your source file(s).
        main.cpp

        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Searches for a package provided by the game activity dependency

find_package(game-activity REQUIRED CONFIG)
find_package(oboe REQUIRED CONFIG)
add_subdirectory(freetype)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        sumobomber

        freetype

        android



        # The game activity
        game-activity::game-activity

        # EGL, required for configuring the display context
        EGL

        # GL ES 2, used for the sample renderer
        GLESv2

        # for AImageDecoder, to load images from resources
        jnigraphics
        oboe::oboe
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})