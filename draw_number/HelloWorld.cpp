/*
	@ Course: Expriment One, 2022 Computer Graphics Course, Hongxin Zhang, Zhejiang University
	@ Author: Shanchen Zou, State Key Laboratory of CAD & CG
	@ Only for Experiment Course
*/

#include <gl/glut.h>
#include <cmath>
#include <iostream>
float fTranslate;
float fRotate;
float fScale = 1.0f;								// set inital scale value to 1.0f
float t = 0;


//draw a 1*1*1 cube
void Draw()
{
	glutWireCube(1.0);
}

void Draw_cubic(float x0, float y0, float z0, float lx, float ly, float lz) {
	GLfloat vertex_list[][3] = {
		x0, y0, z0,
		x0, y0, z0 - lz,
		x0 + lx, y0, z0,
		x0 + lx, y0, z0 - lz,
		x0 + lx,y0 + ly,z0,
		x0 + lx, y0 + ly, z0 - lz,
		x0, y0 + ly, z0,
		x0, y0 + ly, z0 - lz
	};
	const static GLint index_list[][4] = {
		0, 1, 3, 2,
		6, 7, 5, 4,
		0, 2, 4, 6,
		2, 3, 5, 4,
		3, 1, 7, 5,
		1, 0, 6, 7
	};
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			glVertex3fv(vertex_list[index_list[i][j]]);
		}
	}
	glEnd();
}

void Draw_8() {
	Draw_cubic(-0.15, -0.25, 0.05, 0.05, 0.5, 0.10);
	Draw_cubic(.10, -0.25, 0.05, 0.05, 0.5, 0.10);
	Draw_cubic(-0.1, 0.25, 0.05, 0.2, 0.05, 0.1);
	Draw_cubic(-0.1, -0.05, 0.05, 0.2, 0.05, 0.1);
	Draw_cubic(-0.1, -0.3, 0.05, 0.2, 0.05, 0.1);
}

void Draw_4() {
	Draw_cubic(-0.15, 0.0, 0.05, 0.05, 0.25, 0.10);
	Draw_cubic(-0.1, -0.05, 0.05, 0.2, 0.05, 0.1);
	Draw_cubic(.10, -0.25, 0.05, 0.05, 0.5, 0.10);
}

void Draw_1() {
	Draw_cubic(.10, -0.25, 0.05, 0.05, 0.5, 0.10);
}


void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	// Perspective view
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	// Ortho view
	//glOrtho(-4, 4, -4 * (GLfloat)height / (GLfloat)width, 4* (GLfloat)height / (GLfloat)width, 0, 100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void redraw()
{
	t += 0.001;
	if (t >= 1) t -= 1;
	// 如果想使用线框模式
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();									// 重置变换矩阵（回到世界坐标系）

	//The cube on the left
	glPushMatrix(); // 设置一个新的坐标系
	glTranslatef(-2.0f, t, -6.0f);				// 向左平移
	/* @ TODO: where you need to write code to make the cube move along Y-axis.
	*
	*
	*/
	Draw_8();
	glPopMatrix(); // 回到前一个坐标系

	//The cube in the middle
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -6.0f);
	glRotatef(360 * t, 0.0f, 1.0f, 0.0f);
	/* @ TODO: where you need to write code to make the cube rotate arround Y-axis .
	*
	*  如何旋转：glRotatef(19.198f, 0.0f, 1.0f, 0.0f); // 绕轴（0, 1, 0)旋转19.198°（角度制）
	*
	*/
	Draw_4();
	glPopMatrix();

	//The cube on the right
	glPushMatrix();
	glTranslatef(2.0f, 0.0f, -6.0f);
	glScalef(1.0f, 1.0f, 3 * t);
	/* @ TODO: where you need to write code to make the cube scale.
	*
	*	缩放：glScalef(1.0f, 2.0f, 1.0f);    沿着y轴放大一倍
	*/
	Draw_1();
	glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	int windowHandle
		= glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}


