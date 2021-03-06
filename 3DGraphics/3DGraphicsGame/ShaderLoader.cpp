//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: "ShaderLoader.cpp"
// Description	: ShaderLoader implementation file
// Author		: Vivian Ngo & Melanie Jacobson
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

#include "ShaderLoader.h" 

/***********************
* ShaderLoader: ShaderLoader Constructor
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
ShaderLoader::ShaderLoader(void) {}

/***********************
* ~ShaderLoader: ShaderLoader destructor
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
***********************/
ShaderLoader::~ShaderLoader(void) {}

/***********************
* ReadShader: Read Shader file
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: filename - file to read from
***********************/
std::string ShaderLoader::ReadShader(char *filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good()) {
		std::cout << "Can't read file " << filename << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

/***********************
* CreateShader: Creates Shader file
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: shaderType - type of shader
* @parameter: source - shader source
* @parameter: shaderName - name of shader
***********************/
GLuint ShaderLoader::CreateShader(GLenum shaderType, std::string
	source, char* shaderName)
{
	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check for errors
	if (compile_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

/***********************
* CreateProgram: Creates Shader program
* @author: Vivian Ngo & Melanie Jacobson
* @date: 08/05/18
* @parameter: vertexShaderFilename - vertex shader file
* @parameter: fragmentShaderFilename - fragment shader file
***********************/
GLuint ShaderLoader::CreateProgram(char* vertexShaderFilename,
	char* fragmentShaderFilename)
{
	//read the shader files and save the code
	std::string vertex_shader_code = ReadShader(vertexShaderFilename);
	std::string fragment_shader_code = ReadShader(fragmentShaderFilename);

	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;
	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	//check for link errors
	if (link_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return 0;
	}
	return program;
}