#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
map<string, texture> textures;
effect eff;
texture tex;
target_camera cam;
vec3 pos(0.0f, 0.0f, 0.0f);
float dissolve_factor = 1.0f;
vec2 uv_scroll;
texture dissolve;
effect eff1;
effect eff2;
cubemap cube_map;
mesh skybox;
effect sky_eff;
directional_light light;

bool load_content() {

	skybox = mesh(geometry_builder::create_box());
	// Scale box by 100
	skybox.get_transform().scale = vec3(200);
	 
	// Create plane mesh
	meshes["plane"] = mesh(geometry_builder::create_plane());

	array<string, 6> filenames = { "textures/stratosphere_ft.tga", "textures/stratosphere_bk.tga", "textures/stratosphere_up.tga",
		"textures/stratosphere_dn.tga", "textures/stratosphere_rt.tga", "textures/stratosphere_lf.tga" };

	cube_map = cubemap(filenames);

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

	meshes["box_wall1"] = mesh(geometry_builder::create_box());
	meshes["box_wall2"] = mesh(geometry_builder::create_box());
	meshes["box_wall3"] = mesh(geometry_builder::create_box());
	meshes["box_wall4"] = mesh(geometry_builder::create_box());
	meshes["box_wall5"] = mesh(geometry_builder::create_box());
	meshes["door1"] = mesh(geometry_builder::create_box());
	meshes["door2"] = mesh(geometry_builder::create_box());
	meshes["house"] = mesh(geometry_builder::create_box());
	
	meshes["house3"] = mesh(geometry_builder::create_box());
	meshes["pyramid_roof"] = mesh(geometry_builder::create_pyramid());
	meshes["house_roof1"] = mesh(geometry_builder::create_pyramid());
	meshes["house_roof2"] = mesh(geometry_builder::create_pyramid());
	meshes["house4"] = mesh(geometry_builder::create_box());

	// Transform objects
	meshes["box"].get_transform().scale = vec3(10.0f, 10.0f, 10.0f);
	meshes["box"].get_transform().translate(vec3(9.0f, 4.5f, 0.0f));

	meshes["sphere"].get_transform().scale = vec3(4.5f, 4.5f, 4.5f);
	meshes["sphere"].get_transform().translate(vec3(9.0f, 17.5f, 0.0f));
	meshes["sphere"].get_transform().rotate(vec3(half_pi<float>(), 3.0f, 0.0f));

	meshes["box2"].get_transform().scale = vec3(10.0f, 20.0f, 10.0f);
	meshes["box2"].get_transform().translate(vec3(-30.0f, 10.0f, 30.0f));

	meshes["box3"].get_transform().scale = vec3(10.0f, 20.0f, 10.0f);
	meshes["box3"].get_transform().translate(vec3(30.0f, 10.0f, -30.0f));

	meshes["box4"].get_transform().scale = vec3(10.0f, 20.0f, 10.0f);
	meshes["box4"].get_transform().translate(vec3(30.0f, 10.0f, 30.0f));

	meshes["box5"].get_transform().scale = vec3(10.0f, 20.0f, 10.0f);
	meshes["box5"].get_transform().translate(vec3(-30.0f, 10.0f, -30.0f));

	meshes["pyramid"].get_transform().scale = vec3(6.0f, 8.0f, 6.0f);
	meshes["pyramid"].get_transform().translate(vec3(-30.0f, 22.5f, 30.0f));

	meshes["pyramid1"].get_transform().scale = vec3(6.0f, 8.0f, 6.0f);
	meshes["pyramid1"].get_transform().translate(vec3(30.0f, 22.5f, -30.0f));

	meshes["pyramid2"].get_transform().scale = vec3(6.0f, 8.0f, 6.0f);
	meshes["pyramid2"].get_transform().translate(vec3(30.0f, 22.5f, 30.0f));

	meshes["pyramid3"].get_transform().scale = vec3(6.0f, 8.0f, 6.0f);
	meshes["pyramid3"].get_transform().translate(vec3(-30.0f, 22.5f, -30.0f));

	
	meshes["box_wall1"].get_transform().scale = vec3(5.0f, 12.0f, 60.0f);
    meshes["box_wall1"].get_transform().translate(vec3(-30.0f, 6.0f, 0.0f));

	meshes["box_wall2"].get_transform().scale = vec3(5.0f, 12.0f, 15.0f);
	meshes["box_wall2"].get_transform().translate(vec3(30.0f, 6.0f, 20.0f));

	meshes["box_wall3"].get_transform().scale = vec3(60.0f, 12.0f, 5.0f);
	meshes["box_wall3"].get_transform().translate(vec3(0.0f, 6.0f, -30.0f));

	meshes["box_wall4"].get_transform().scale = vec3(60.0f, 12.0f, 5.0f);
	meshes["box_wall4"].get_transform().translate(vec3(0.0f, 6.0f, 30.0f));

	meshes["box_wall5"].get_transform().scale = vec3(5.0f, 12.0f, 15.0f);
	meshes["box_wall5"].get_transform().translate(vec3(30.0f, 6.0f, -20.0f));

	meshes["door1"].get_transform().scale = vec3(10.0f, 15.0f, 2.0f);
	meshes["door1"].get_transform().translate(vec3(24.0f, 7.5f, -11.3f));

	meshes["door2"].get_transform().scale = vec3(10.0f, 15.0f, 2.0f);
	meshes["door2"].get_transform().translate(vec3(24.0f, 7.5f, 11.3f));

	meshes["house"].get_transform().scale = vec3(26.0f, 24.0f, 30.0f);
	meshes["house"].get_transform().translate(vec3(-12.0f, 11.5f, 0.0f));

	meshes["pyramid_roof"].get_transform().scale = vec3(28.0f, 12.0f, 32.0f);
	meshes["pyramid_roof"].get_transform().translate(vec3(-12.0f, 29.0f, 0.0f));

	

	meshes["house3"].get_transform().scale = vec3(15.0f, 15.0f, 8.0f);
	meshes["house3"].get_transform().translate(vec3(12.0f, 12.5f, -20.0f));

	meshes["house4"].get_transform().scale = vec3(15.0f, 15.0f, 8.0f);
	meshes["house4"].get_transform().translate(vec3(12.0f, 12.5f, 20.0f));

	meshes["house_roof1"].get_transform().scale = vec3(17.0f, 4.0f, 9.0f);
	meshes["house_roof1"].get_transform().translate(vec3(12.0f, 22.0f, 20.0f));

	meshes["house_roof2"].get_transform().scale = vec3(17.0f, 4.0f, 9.0f);
	meshes["house_roof2"].get_transform().translate(vec3(12.0f, 22.0f, -20.0f));

	// Load texture
	tex = texture("textures/water-06.jpg");
	textures["box"] = texture("textures/wood2.jpg");
	textures["box2"] = texture("textures/wood_1.jpg");
	textures["box3"] = texture("textures/wood_1.jpg");
	textures["box4"] = texture("textures/wood_1.jpg");
	textures["box5"] = texture("textures/wood_1.jpg");
	textures["box_wall1"] = texture("textures/Brick-Wal_01.jpg");
	textures["box_wall2"] = texture("textures/Brick-Wal_01.jpg");
	textures["box_wall3"] = texture("textures/Brick-Wal_01.jpg");
	textures["box_wall4"] = texture("textures/Brick-Wal_01.jpg");
	textures["box_wall5"] = texture("textures/Brick-Wal_01.jpg");
	textures["plane"] = texture("textures/brick_wall_texture.jpg");
	textures["pyramid"] = texture("textures/stone floor 2.jpg");
	textures["pyramid1"] = texture("textures/stone floor 2.jpg");
	textures["pyramid2"] = texture("textures/stone floor 2.jpg");
	textures["pyramid3"] = texture("textures/stone floor 2.jpg");
	textures["door1"] = texture("textures/Wood4.jpg");
	textures["door2"] = texture("textures/Wood4.jpg");
	textures["house"] = texture("textures/brick_wall01.jpg");
	textures["pyramid_roof"] = texture("textures/metal roof2.jpg");
	textures["house_roof1"] = texture("textures/metal roof2.jpg");
	textures["house_roof2"] = texture("textures/metal roof2.jpg");
	
	textures["house3"] = texture("textures/brick_wall01.jpg");
	textures["house4"] = texture("textures/brick_wall01.jpg");


	
    dissolve = texture("textures/world-blend-map.png");

	// Set lighting values
	// ambient intensity (0.3, 0.3, 0.3)
	light.set_ambient_intensity(vec4(0.3f, 0.3f, 0.3f, 1.0f));
	// Light colour white
	light.set_light_colour(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	// Light direction (1.0, 1.0, -1.0)
	light.set_direction(vec3(1.0, 1.0, -1.0));
	// Load in shaders
	eff2.add_shader("shaders/gouraud.vert", GL_VERTEX_SHADER);
	eff2.add_shader("shaders/gouraud.frag", GL_FRAGMENT_SHADER);

	// Load in shaders
	
	eff.add_shader("shaders/dissolve.vert", GL_VERTEX_SHADER);
	eff.add_shader("shaders/dissolve.frag", GL_FRAGMENT_SHADER);

	eff1.add_shader("shaders/simple_texture.vert", GL_VERTEX_SHADER);
	eff1.add_shader("shaders/simple_texture.frag", GL_FRAGMENT_SHADER);

	sky_eff.add_shader("shaders/skybox.vert", GL_VERTEX_SHADER);
	sky_eff.add_shader("shaders/skybox.frag", GL_FRAGMENT_SHADER);

	
	

	// Build effect
	eff.build();
	eff1.build();
	sky_eff.build();
	eff2.build();

	// Set camera properties
	cam.set_position(vec3(100.0f, 50.0f, 50.0f));
	cam.set_target(vec3(0.0f, 1.0f, 0.0f));
	cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);
	return true;
}


bool update(float delta_time) {
	
	

	skybox.get_transform().position = cam.get_position();
	// *********************************
	// Use keyboard to change camera location
		
	// 1 - (80.0f, 50.0f, 0.0f)
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_1)) {
		cam.set_position(vec3(120.0f, 30.0f, 0.0f));
	}

	// 2 - (50.0f, 50.0f, -50.0f)
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_2)) {
		cam.set_position(vec3(90.0f, 50.0f, -50.0f));
	}
	
	// 3 - (0.0f, 50.0f, -80.0f)
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_3)) {
		cam.set_position(vec3(0.0f, 50.0f, -110.0f));
	}

	// 7 - (0.0f, 10.0f, -110.0f)
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_7)) {
		cam.set_position(vec3(0.0f, 10.0f, -110.0f));
	}

	// 4 - (-50.0f, 50.0f, -70.0f)
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_4)) {
		cam.set_position(vec3(-50.0f, 50.0f, -90.0f));
	}

	// 5 - (-90.0f, 70.0f, 0.0f)
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_5)) {
		cam.set_position(vec3(-90.0f, 70.0f, 0.0f));
	}
	
	// 6 - (50, 90, 0)
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_6)) {
		cam.set_position(vec3(50.0f, 90.0f, 0.0f));
	}

	// 0 - (50, 50, 50) DEFAULT POSITION
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_0)) {
		cam.set_position(vec3(100.0f, 50.0f, 50.0f));
	}

	// 8 - (70.0f, 20.0f, 50.0f)
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_8)) {
		cam.set_position(vec3(70.0f, 20.0f, 50.0f));
	}

	meshes["box"].get_transform().rotate(vec3(0.0f, half_pi<float>(), 0.0f) * delta_time);

	meshes["pyramid"].get_transform().rotate(vec3(0.0f, half_pi<float>(), 0.0f) * delta_time);
	meshes["pyramid1"].get_transform().rotate(vec3(0.0f, half_pi<float>(), 0.0f) * delta_time);
	meshes["pyramid2"].get_transform().rotate(vec3(0.0f, half_pi<float>(), 0.0f) * delta_time);
	meshes["pyramid3"].get_transform().rotate(vec3(0.0f, half_pi<float>(), 0.0f) * delta_time);


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

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glCullFace(GL_FRONT);

	renderer::bind(sky_eff);

	auto M = skybox.get_transform().get_transform_matrix();
	auto V = cam.get_view();
	auto P = cam.get_projection();
	auto MVP = P*V*M;

	// Set MVP matrix uniform
	glUniformMatrix4fv(sky_eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));

	renderer::bind(cube_map, 0);

	renderer::render(skybox);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glCullFace(GL_BACK);

	// Render meshes
	for (auto &e : meshes) {
		if (e.first == "sphere") {
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
		else
		{
			
			auto m = e.second;
			// Bind effect
			renderer::bind(eff2);
			
			// Create MVP matrix
			auto M = m.get_transform().get_transform_matrix();
			auto V = cam.get_view();
			auto P = cam.get_projection();
			auto MVP = P * V * M;
			// Set MVP matrix uniform
			glUniformMatrix4fv(eff2.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));

			//glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
			// *********************************
			// Set M matrix uniform
			glUniformMatrix4fv(eff2.get_uniform_location("M"), 1, GL_FALSE, value_ptr(M));

			// Set N matrix uniform - remember - 3x3 matrix 
			mat3 normalmat = m.get_transform().get_normal_matrix();
			glUniformMatrix3fv(eff2.get_uniform_location("N"), 1, GL_FALSE, value_ptr(normalmat));

			renderer::bind(m.get_material(), "mat");
			// Bind light
			renderer::bind(light, "light");
			// Bind texture
			renderer::bind(tex, 0);

			// Set tex uniform
			glUniform1i(eff.get_uniform_location(" tex"), 0);

			// Set eye position - Get this from active camera
			glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(vec3(50.0f, 10.0f, 50.0f)));

			// Bind and set texture
			texture t = tex;

			//search for the texture name in textures
			auto it = textures.find(e.first);
			if (it != textures.end()) {
				//we found it!
				t = textures[e.first];
			}
	
			renderer::bind(t,0);
			
			// Set the uniform values for textures - use correct index
			glUniform1i(eff2.get_uniform_location("tex"), 0);
			
			// Render mesh
		renderer::render(m);
		}

		
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