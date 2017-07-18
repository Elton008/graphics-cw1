#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
effect eff;
texture tex;
target_camera cam;
vec3 pos(0.0f, 0.0f, 0.0f);
float dissolve_factor = 1.0f;
vec2 uv_scroll;
texture dissolve;

bool load_content() {
	// Create plane mesh
	meshes["plane"] = mesh(geometry_builder::create_plane());

	// Create scene
	meshes["box"] = mesh(geometry_builder::create_box());
	meshes["sphere"] = mesh(geometry_builder::create_sphere(20, 20));
	meshes["box2"] = mesh(geometry_builder::create_box());
	meshes["box3"] = mesh(geometry_builder::create_box());
	meshes["box4"] = mesh(geometry_builder::create_box());
	meshes["box5"] = mesh(geometry_builder::create_box());
	meshes["pyramid"] = mesh(geometry_builder::create_pyramid());
	meshes["pyramid1"] = mesh(geometry_builder::create_pyramid());
	meshes["pyramid2"] = mesh(geometry_builder::create_pyramid());
	meshes["pyramid3"] = mesh(geometry_builder::create_pyramid());

	/*/meshes["tetra"] = mesh(geometry_builder::create_tetrahedron());
	meshes["pyramid"] = mesh(geometry_builder::create_pyramid());
	meshes["disk"] = mesh(geometry_builder::create_disk(20));
	meshes["cylinder"] = mesh(geometry_builder::create_cylinder(20, 20));
	meshes["sphere"] = mesh(geometry_builder::create_sphere(20, 20));
	meshes["torus"] = mesh(geometry_builder::create_torus(20, 20, 1.0f, 5.0f));
/*/
	// Transform objects
	meshes["box"].get_transform().scale = vec3(10.0f, 10.0f, 10.0f);
	meshes["box"].get_transform().translate(vec3(0.0f, 2.5f, 0.0f));

	meshes["sphere"].get_transform().scale = vec3(4.5f, 4.5f, 4.5f);
	meshes["sphere"].get_transform().translate(vec3(0.0f, 17.5f, 0.0f));

	meshes["box2"].get_transform().scale = vec3(10.0f, 20.0f, 10.0f);
	meshes["box2"].get_transform().translate(vec3(-30.0f, 2.5f, 30.0f));

	meshes["box3"].get_transform().scale = vec3(10.0f, 20.0f, 10.0f);
	meshes["box3"].get_transform().translate(vec3(30.0f, 2.5f, -30.0f));

	meshes["box4"].get_transform().scale = vec3(10.0f, 20.0f, 10.0f);
	meshes["box4"].get_transform().translate(vec3(30.0f, 2.5f, 30.0f));

	meshes["box5"].get_transform().scale = vec3(10.0f, 20.0f, 10.0f);
	meshes["box5"].get_transform().translate(vec3(-30.0f, 2.5f, -30.0f));

	meshes["pyramid"].get_transform().scale = vec3(10.0f, 10.0f, 10.0f);
	meshes["pyramid"].get_transform().translate(vec3(-30.0f, 17.5f, 30.0f));

	meshes["pyramid1"].get_transform().scale = vec3(10.0f, 10.0f, 10.0f);
	meshes["pyramid1"].get_transform().translate(vec3(30.0f, 17.5f, -30.0f));

	meshes["pyramid2"].get_transform().scale = vec3(10.0f, 10.0f, 10.0f);
	meshes["pyramid2"].get_transform().translate(vec3(30.0f, 17.5f, 30.0f));

	meshes["pyramid3"].get_transform().scale = vec3(10.0f, 10.0f, 10.0f);
	meshes["pyramid3"].get_transform().translate(vec3(-30.0f, 17.5f, -30.0f));

	


	/*/meshes["tetra"].get_transform().scale = vec3(4.0f, 4.0f, 4.0f);
	meshes["tetra"].get_transform().translate(vec3(-30.0f, 10.0f, -10.0f));
	meshes["pyramid"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["pyramid"].get_transform().translate(vec3(-10.0f, 7.5f, -30.0f));
	meshes["disk"].get_transform().scale = vec3(3.0f, 1.0f, 3.0f);
	meshes["disk"].get_transform().translate(vec3(-10.0f, 11.5f, -30.0f));
	meshes["disk"].get_transform().rotate(vec3(half_pi<float>(), 0.0f, 0.0f));
	meshes["cylinder"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["cylinder"].get_transform().translate(vec3(-25.0f, 2.5f, -25.0f));
	meshes["sphere"].get_transform().scale = vec3(2.5f, 2.5f, 2.5f);
	meshes["sphere"].get_transform().translate(vec3(-25.0f, 10.0f, -25.0f));
	meshes["torus"].get_transform().translate(vec3(-25.0f, 10.0f, -25.0f));
	meshes["torus"].get_transform().rotate(vec3(half_pi<float>(), 0.0f, 0.0f));
/*/
	// Load texture
	tex = texture("textures/water-06.jpg");

	//meshes["box"] = texture("textures/water-06.jpg");

	//plane_tex = texture("textures/night clouds 1.jpg");
	//tex = texture("textures/blue_sky.jpg");
	dissolve = texture("textures/world-blend-map.png");


	// Load in shaders
	//eff.add_shader("shaders/simple_texture.vert", GL_VERTEX_SHADER);
	//eff.add_shader("shaders/simple_texture.frag", GL_FRAGMENT_SHADER);

	eff.add_shader("shaders/dissolve.vert", GL_VERTEX_SHADER);
	eff.add_shader("shaders/dissolve.frag", GL_FRAGMENT_SHADER);


	// Build effect
	eff.build();

	// Set camera properties
	cam.set_position(vec3(50.0f, 50.0f, 50.0f));
	cam.set_target(vec3(0.0f, 1.0f, 0.0f));
	cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);
	return true;
}

bool update(float delta_time) {
	// *********************************
	// Use keyboard to change camera location
	// 1 - (50, 10, 50)
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_1)) {
		cam.set_position(vec3(-50.0f, 50.0f, 0.0f));
	}

	

	// 2 - (-50, 50, 50)
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_2)) {
		cam.set_position(vec3(50.0f, 10.0f, 50.0f));
	}


	// 3 - (-50, 50, -50)

	if (glfwGetKey(renderer::get_window(), GLFW_KEY_3)) {
		cam.set_position(vec3(-50.0f, 10.0f, 00.0f));
	}

	// 4 - (50, 50, -50)


	if (glfwGetKey(renderer::get_window(), GLFW_KEY_4)) {
		cam.set_position(vec3(50.0f, 100.0f, -50.0f));
	}
	// 5 - ()
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_5)) {
		cam.set_position(vec3(50.0f, 100.0f, 00.0f));
	}

	//0 - (50, 50, 50) default
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_0)) {
		cam.set_position(vec3(50.0f, 50.0f, 50.0f));
	}


	// Use up an down to modify the dissolve factor
	//UP direction
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_UP))
		dissolve_factor = clamp(dissolve_factor + 0.1f * delta_time, 0.0f, 1.0f);

	//DOWN direction
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_DOWN))
		dissolve_factor = clamp(dissolve_factor - 0.1f * delta_time, 0.0f, 1.0f);

		// Update the camera
	cam.update(delta_time);
	// *********************************
	uv_scroll += vec2(0, delta_time * 0.05);
	return true;
}

bool render() {
	// Render meshes
	for (auto &e : meshes) {
		auto m = e.second;
		// Bind effect
		renderer::bind(eff);
		// Create MVP matrix
		auto M = m.get_transform().get_transform_matrix();
		auto V = cam.get_view();
		auto P = cam.get_projection();
		auto MVP = P * V * M;
		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));


		// Set the dissolve_factor uniform value
		glUniform1f(eff.get_uniform_location("dissolve_factor"), dissolve_factor);

		// Bind and set texture
		renderer::bind(tex, 0);
		renderer::bind(dissolve, 1);

		// Set the uniform values for textures - use correct index
		glUniform1i(eff.get_uniform_location("tex"), 0);
		glUniform1i(eff.get_uniform_location("dissolve"), 1);


		// Set UV_scroll uniform, adds cool movent (Protip: This is a super easy way to do fire effects;))
		glUniform2fv(eff.get_uniform_location("UV_SCROLL"), 1, value_ptr(uv_scroll));
		// Render the mesh
		

		// Render mesh
		renderer::render(m);
	}

	return true;
}

void main() {
	// Create application
	app application("37_Target_Camera");
	// Set load content, update and render methods
	application.set_load_content(load_content);
	application.set_update(update);
	application.set_render(render);
	// Run application
	application.run();
}