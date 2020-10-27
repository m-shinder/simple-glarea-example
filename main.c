#include <gtk/gtk.h>
#include <epoxy/gl.h>

const char *vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;"
"void main()"
"{"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
"}";

const char *fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor;"
"void main()"
"{"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
"}";

int shaderProgram;
unsigned int VBO; 
unsigned int VAO;

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

void buildShaderProgram()
{
	int vertexShader;
	int fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
void on_realize (GtkGLArea *area)
{
	gtk_gl_area_make_current (area);
	if (gtk_gl_area_get_error (area) != NULL)
		return;

	buildShaderProgram();

	glGenVertexArrays(1, &VAO); 
	glBindVertexArray(VAO); 

	glGenBuffers(1, &VBO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 
}

void draw_triangle()
{

	glClearColor(0.7f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO); 
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0); 
	glUseProgram(0);
	glFlush();
}

gboolean render(GtkWidget *glarea, gpointer data)
{
	gtk_gl_area_make_current (GTK_GL_AREA(glarea));

	draw_triangle();

	return FALSE;
}

void activate(GtkApplication* app, gpointer user_data)
{
	GtkWidget	*window;
	GtkWidget	*glarea;
	
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Simple GLarea Example");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

	glarea = gtk_gl_area_new();
	g_signal_connect(glarea, "realize", G_CALLBACK(on_realize), NULL);
	g_signal_connect(glarea, "render", G_CALLBACK(render), NULL);
	gtk_container_add(GTK_CONTAINER(window), glarea);

	gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
	GtkApplication *app;
	int status = 0;

	app = gtk_application_new("com.example.glarea", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
