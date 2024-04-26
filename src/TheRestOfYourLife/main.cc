//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "camera.h"
#include "constant_medium.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "quad.h"
#include "sphere.h"


int main() {
    hittable_list world;

    auto red   = make_shared<lambertian>(color(.198, .0, .0));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    auto senna_texture = make_shared<image_texture>("senna.jpg");
    auto senna_surface = make_shared<lambertian>(senna_texture);

    auto senna_capacete_texture = make_shared<image_texture>("senna_capacete.jpg");
    auto senna_capacete_surface = make_shared<lambertian>(senna_capacete_texture);

    auto senna_logo_texture = make_shared<image_texture>("senna_logo.png");
    auto senna_logo_surface = make_shared<lambertian>(senna_logo_texture);

    auto interlagos_texture = make_shared<image_texture>("interlagos.png");
    auto interlagos_surface = make_shared<lambertian>(interlagos_texture);

    // Cornell box sides
    //world.add(make_shared<quad>(point3(555,0,0), vec3(0,0,555), vec3(0,555,0), red));
    world.add(make_shared<quad>(point3(0,0,555), vec3(0,0,-555), vec3(0,555,0), interlagos_surface));
    world.add(make_shared<quad>(point3(0,555,0), vec3(555,0,0), vec3(0,0,555), white));
    world.add(make_shared<quad>(point3(0,0,555), vec3(555,0,0), vec3(0,0,-555), white));
    world.add(make_shared<quad>(point3(555,0,555), vec3(-555,0,0), vec3(0,555,0), senna_surface));

    // Light
    world.add(make_shared<quad>(point3(213,554,122), vec3(130,0,0), vec3(0,0,433), light));

    // Box
    shared_ptr<hittable> box1 = box(point3(0,0,0), point3(165,200,165), senna_logo_surface);
    box1 = make_shared<rotate_y>(box1, 120);
    box1 = make_shared<translate>(box1, vec3(150,0,350));
    world.add(box1);

   /*  shared_ptr<hittable> quadro_interlagos = box(point3(200,200,0), point3(300,250,100), interlagos_surface);
    quadro_interlagos = make_shared<rotate_y>(quadro_interlagos, 120);
    quadro_interlagos = make_shared<translate>(quadro_interlagos, vec3(270,0,450));
    world.add(quadro_interlagos); */

    shared_ptr<hittable> senna_capacete = make_shared<sphere>(point3(300,100,190), 100, senna_capacete_surface);
    senna_capacete = make_shared<rotate_y>(senna_capacete, 60);
    senna_capacete = make_shared<translate>(senna_capacete, vec3(100,0,450));

    shared_ptr<hittable> senna_capacete_menor = make_shared<sphere>(point3(300,60,100), 60, senna_capacete_surface);

    world.add(senna_capacete);
    world.add(senna_capacete_menor);

    // Light Sources
    hittable_list lights;
    auto m = shared_ptr<material>();
    lights.add(make_shared<quad>(point3(343,554,332), vec3(-130,0,0), vec3(0,0,-105), m));
    //lights.add(make_shared<sphere>(point3(190, 90, 190), 90, m));

    camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 800;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = color(0,0,0);

    cam.vfov     = 40;
    cam.lookfrom = point3(278, 278, -800);
    cam.lookat   = point3(278, 278, 0);
    cam.vup      = vec3(0, 1, 0);

    cam.defocus_angle = 0;

    cam.render(world, lights);
}
