global_env = DefaultEnvironment()

def remove_unused(env, node):
    if ("example" in node.get_path()): return None
    if ("misc" in node.get_path()): return None

    backend_files = [
        "imgui_impl_glfw.cpp",
        "imgui_impl_opengl3.cpp",
    ]

    if ("backend" in node.get_path()):
        if (node.name in backend_files): return node
        else: return None

    return node

global_env.AddBuildMiddleware(remove_unused, "*/imgui/*")