static const char VERTEX_SHADER[] = 
    "#version 330 core\n"
    "layout(location = 1) in vec2 pos;\n"
    "in vec2 tc;\n"
    "out vec2 v_tc;\n"
    "void main() {\n"
    "    gl_Position = vec4(pos, 0.0, 1.0);\n"
    "    v_tc = tc;\n"
    "}\n";

static const char FRAGMENT_SHADER[] =
    "#version 330 core\n"
    "in vec2 v_tc;\n"
    "out vec4 out_color;\n"
    "void main() {\n"
    "    out_color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";


static const float VERTICS[] = {
    -0.75f, -0.75f,
    0.75f, -0.75f,
    -0.75f, 0.75f,
    0.75f, 0.75f
};
