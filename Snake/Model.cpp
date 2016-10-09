#include "Model.h"


Model::Model()
{
	shader = new Shader(VERETXSHADERPATH, FRAGMENTSHADERPATH);
	cout << "LOADING...";
	loadOBJ(".\\OBJ\\cube.obj");
	//load_obj();
	cout << "LOADED";
	generateBuffer();
	interpretVertexData();
	//loadTexture();
	scaleMultiplier = 0.15f;
	//baseModel = rotate(baseModel, glm::radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	baseModel = translate(baseModel, vec3(0.0f, scaleMultiplier, 0.0f));
	baseModel = scale(baseModel, vec3(scaleMultiplier, scaleMultiplier, scaleMultiplier));
}


Model::~Model()
{
}

//na podstawie: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
bool Model::loadOBJ(const char * path)
{
	printf("Loading %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec4> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec4> temp_normals;


	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Can't open the file...\n");
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec4 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertex.w = 1.0f;
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			//uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec4 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normal.w = 0.0f;
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				//  return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			//char stupidBuffer[1000];
			//fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i<vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec4 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec4 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		vertices.push_back(vertex);
		uvs.push_back(uv);
		normals.push_back(normal);

	}

	return true;
}

void Model::generateBuffer() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	genBuf(&VERTEX, vertices);
	genBuf(&UV, uvs);
	genBuf(&NORMAL, normals);

};

void Model::interpretVertexData() {
	glBindBuffer(GL_ARRAY_BUFFER, VERTEX);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, UV);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, NORMAL);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);
};

template <typename T>
void Model::genBuf(GLuint *handle, vector<T> data){
	cout << data.size() << endl;
	glGenBuffers(1, handle);
	glBindBuffer(GL_ARRAY_BUFFER, *handle);
	glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(T), &data[0], GL_STATIC_DRAW);
};

void Model::transformCoordinates(mat4* view, mat4* projection) {
	modelLoc = glGetUniformLocation(shader->Program, "model");
	viewLoc = glGetUniformLocation(shader->Program, "view");
	projectionLoc = glGetUniformLocation(shader->Program, "projection");
	GLint light1ColorLoc = glGetUniformLocation(shader->Program, "light1Color");
	GLint light1PosLoc = glGetUniformLocation(shader->Program, "light1Pos");
	GLint light2ColorLoc = glGetUniformLocation(shader->Program, "light2Color");
	GLint light2PosLoc = glGetUniformLocation(shader->Program, "light2Pos");
	GLint viewPosLoc = glGetUniformLocation(shader->Program, "viewPos");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(*view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(*projection));
	glUniform3f(light1ColorLoc, 1.0f, 0.0f, 0.0f);
	glUniform3f(light1PosLoc, -100.0f, 16.0f, 10.0f);
	glUniform3f(light2ColorLoc, 0.0f, 0.0f, 1.0f);
	glUniform3f(light2PosLoc, 20.0f, 70.0f, 5.0f);
	glUniform3f(viewPosLoc, 0.0f, 10.0f, 0.0f);
};

void Model::draw(mat4* view, mat4* projection) {
	glBindTexture(GL_TEXTURE_2D, texture);
	shader->Use();
	glBindVertexArray(VAO);
	model = baseModel;
	transformCoordinates(view, projection);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//cout << vertices.size();
	//cout << "APPLE POS: " << 0 << "  " << 0 << endl;
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
};

void Model::loadTexture() {
	int locWidth, locHeight;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image(IMAGEPATH, &locWidth, &locHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, locWidth, locHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}
