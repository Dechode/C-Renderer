#include "renderer.h"
#include <SDL2/SDL_video.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static RenderState2D renderState;

SDL_Window* initWindow(uint32_t width, uint32_t height, const char* title)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
        printf("Could not init SDL!: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window *window = SDL_CreateWindow(title , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    if (!window)
	{
        printf("Could not init window!: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

	renderState.windowHeight = height;
	renderState.windowWidth = width;

    SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
        printf("Could not init GL!: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    puts("OpenGL Loaded!");
    printf("Vendor = %s\n", glGetString(GL_VENDOR));
    printf("Renderer = %s\n", glGetString(GL_RENDERER));
    printf("Version = %s\n", glGetString(GL_VERSION));

    return window;
}

uint32_t createShader(const char *pathFrag, const char *pathVert)
{
    int success;
    char log[512];

    File fileVertex = ioReadFile(pathVert);
    if (!fileVertex.isValid)
	{
        printf("Error reading vertex shader: %s\n", pathVert);
		exit(EXIT_FAILURE);
    }

    uint32_t shaderVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderVertex, 1, (const char *const *)&fileVertex, NULL);
    glCompileShader(shaderVertex);
    glGetShaderiv(shaderVertex, GL_COMPILE_STATUS, &success);
    if (!success)
	{
        glGetShaderInfoLog(shaderVertex, 512, NULL, log);
        printf("Error compiling vertex shader: %s\n", log);
		exit(EXIT_FAILURE);
    }

    File fileFragment = ioReadFile(pathFrag);
    if (!fileFragment.isValid)
	{
        printf("Error reading fragment shader: %s\n", pathFrag);
		exit(EXIT_FAILURE);
    }

    uint32_t shaderFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderFragment, 1, (const char *const *)&fileFragment, NULL);
    glCompileShader(shaderFragment);
    glGetShaderiv(shaderFragment, GL_COMPILE_STATUS, &success);
    if (!success)
	{
        glGetShaderInfoLog(shaderFragment, 512, NULL, log);
        printf("Error compiling fragment shader: %s\n", log);
		exit(EXIT_FAILURE);
    }

    uint32_t shader = glCreateProgram();
    glAttachShader(shader, shaderVertex);
    glAttachShader(shader, shaderFragment);
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success)
	{
        glGetProgramInfoLog(shader, 512, NULL, log);
        printf("Error linking shader: %s\n", log);
		exit(EXIT_FAILURE);
    }

    free(fileVertex.data);
    free(fileFragment.data);

    return shader;
}

void initImageTexture(ImageTexture* imgTex, const char* path)
{
	imgTex->textureData = NULL;
	imgTex->width = 0;
	imgTex->height = 0;
	imgTex->numChannels = 0;

	stbi_set_flip_vertically_on_load(1);
	imgTex->textureData = stbi_load(path, &imgTex->width, &imgTex->height, &imgTex->numChannels, 0);

	glGenTextures(1, &imgTex->texture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, imgTex->texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (!imgTex->textureData)
	{
		puts("ERROR: Could not load image");
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, imgTex->width, imgTex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgTex->textureData);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(imgTex->textureData);
}

void initShaders(RenderState2D *state)
{
    state->shaderDefault = createShader("shaders/default.frag.glsl", "shaders/default.vert.glsl");

    mat4x4_ortho(state->projection, 0, state->windowWidth, 0, state->windowHeight, -2, 2);

    glUseProgram(state->shaderDefault);
    glUniformMatrix4fv(glGetUniformLocation(state->shaderDefault, "projection"), 1, GL_FALSE, &state->projection[0][0]);
}

void initColorTexture(uint32_t* texture)
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    uint8_t solidWhite[4] = {255,255,255,255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, solidWhite);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void initSprite(Sprite* sprite, ImageTexture* texture, uint32_t width, uint32_t height, vec3 pos)
{

	sprite->width = width;
	sprite->height = height;
	memcpy(pos, sprite->position, sizeof(sprite->position));
//	sprite.position = pos;
}

void initTriangle(uint32_t *vao, uint32_t *vbo)
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, vao);
	glGenBuffers(1, vbo);
	glBindVertexArray(*vao);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void initQuad(uint32_t *vao, uint32_t *vbo, uint32_t *ebo)
{
    float vertices[] = {
        0.5, 0.5, 0, 0, 0,
        0.5, -0.5, 0, 0, 1,
        -0.5, -0.5, 0, 1, 1,
        -0.5, 0.5, 0, 1, 0
    };

    uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, vao);
    glGenBuffers(1, vbo);
    glGenBuffers(1, ebo);

    glBindVertexArray(*vao);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glad_glEnableVertexAttribArray(1);
}

void initLine(uint32_t *vao, uint32_t *vbo)
{
    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void initRenderer(void)
{
//	window = initWindow(width, height, title);
	initTriangle(&renderState.triangleVao, &renderState.triangleVbo);
	initQuad(&renderState.quadVao, &renderState.quadVbo, &renderState.quadEbo);
    initLine(&renderState.lineVao, &renderState.lineVbo);
    initShaders(&renderState);
    initColorTexture(&renderState.colorTexture);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void renderBegin(void)
{
    glClearColor(0.08, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderEnd(SDL_Window* window)
{
    SDL_GL_SwapWindow(window);
}

void renderQuad(vec2 pos, vec2 size, vec4 color)
{
    glUseProgram(renderState.shaderDefault);

    mat4x4 model;
    mat4x4_identity(model);

    mat4x4_translate(model, pos[0], pos[1], 0);
    mat4x4_scale_aniso(model, model, size[0], size[1], 1);

    glUniformMatrix4fv(glGetUniformLocation(renderState.shaderDefault, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform4fv(glGetUniformLocation(renderState.shaderDefault, "color"),1, color);

    glBindVertexArray(renderState.quadVao);
    glBindTexture(GL_TEXTURE_2D, renderState.colorTexture);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

void renderTriangle(vec2 pos, vec2 size, vec4 color)
{
	glUseProgram(renderState.shaderDefault);
	mat4x4 model;
    mat4x4_identity(model);

    mat4x4_translate(model, pos[0], pos[1], 0);
    mat4x4_scale_aniso(model, model, size[0], size[1], 1);

    glUniformMatrix4fv(glGetUniformLocation(renderState.shaderDefault, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform4fv(glGetUniformLocation(renderState.shaderDefault, "color"),1, color);
	glBindVertexArray(renderState.triangleVao);
	glBindTexture(GL_TEXTURE_2D, renderState.colorTexture);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void renderLineSegment(vec2 start, vec2 end, vec4 color, int lineWidth)
{
    glUseProgram(renderState.shaderDefault);
    glLineWidth(lineWidth);

    float x = end[0] - start[0];
    float y = end[1] - start[1];
    float line[6] = {0, 0, 0, x, y, 0};

    mat4x4 model;
    mat4x4_translate(model, start[0], start[1], 0);

    glUniformMatrix4fv(glGetUniformLocation(
                    renderState.shaderDefault, "model"),
                    1, GL_FALSE, &model[0][0]);
    glUniform4fv(glGetUniformLocation(renderState.shaderDefault, "color"), 1, color);

    glBindTexture(GL_TEXTURE_2D, renderState.colorTexture);
    glBindVertexArray(renderState.lineVao);

    glBindBuffer(GL_ARRAY_BUFFER, renderState.lineVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(line), line);
    glDrawArrays(GL_LINES, 0, 2);

    glBindVertexArray(0);
}

void renderQuadLine(vec2 pos, vec2 size, vec4 color, int lineWidth)
{
    vec2 points[4] = {
        {pos[0] - size[0] * 0.5f, pos[1] - size[1] * 0.5},
        {pos[0] + size[0] * 0.5f, pos[1] - size[1] * 0.5},
        {pos[0] + size[0] * 0.5f, pos[1] + size[1] * 0.5},
        {pos[0] - size[0] * 0.5f, pos[1] + size[1] * 0.5},
    };

    renderLineSegment(points[0], points[1], color, lineWidth);
    renderLineSegment(points[1], points[2], color, lineWidth);
    renderLineSegment(points[2], points[3], color, lineWidth);
    renderLineSegment(points[3], points[0], color, lineWidth);
}


