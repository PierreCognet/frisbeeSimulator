#ifndef PRJ_GLSPHERE_H
#define PRJ_GLSPHERE_H

#include <QGLBuffer>
#include <QGLShaderProgram>

class GLSphere {
public:
	GLSphere()
	: vbo(QGLBuffer::VertexBuffer), ibo(QGLBuffer::IndexBuffer) {}

	void initialize(GLuint slices = 15, GLuint stacks = 15);

	void draw(QGLShaderProgram& program, int attributeLocation);

	void bind();
	void release();

private:
	QGLBuffer vbo, ibo;
	GLuint vbo_sz;
	GLuint ibo_sz[3];
};

#endif
