# Needed to compile Box2D properly
global_env = DefaultEnvironment()
global_env.Append(CXXFLAGS=["-std=gnu++11"])