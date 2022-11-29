/**
 * Martin Egli
 * 2022-11-28
 * main part for hot wire game: housing display, arduino and sound
 */

use <parts.scad>


module case1(show = 1, loc_res = 32) {
    disp_x = 20;
    disp_wid = 27;
    if(show) {
        translate([disp_x, -28/2, -4])
        displayPCB();
        translate([6, -18/2, -12])
        rotate([0, 0, 90])
        switch();
        translate([75, 0, -2])
        speaker2W();
        
        translate([25, -10, -15])
        arduinoMicroProPCB();
    }
    difference() {
        union() {
            hull() {
                translate([-15, -20, -2])
                cylinder(d = 4, h = 2, $fn = loc_res);
                translate([-15, +20, -2])
                cylinder(d = 4, h = 2, $fn = loc_res);
                translate([100, -20, -2])
                cylinder(d = 4, h = 2, $fn = loc_res);
                translate([100, +20, -2])
                cylinder(d = 4, h = 2, $fn = loc_res);
            }
            translate([0, 0, -3]) {
                hull() {
                    translate([disp_x-4/2-0.5, -28/2+2, -1])
                    cylinder(d = 4, h = 2, $fn = loc_res);
                    translate([disp_x-4/2-0.5, +28/2-2, -1])
                    cylinder(d = 4, h = 2, $fn = loc_res);
                }
                hull() {
                    translate([disp_x-4/2-0.5, -28/2+2, 0])
                    cylinder(d = 4, h = 1, $fn = loc_res);
                    translate([disp_x-4/2-0.2+8, -28/2+2, 0])
                    cylinder(d = 4, h = 1, $fn = loc_res);
                }
                hull() {
                    translate([disp_x-4/2-0.5, +28/2-2, 0])
                    cylinder(d = 4, h = 1, $fn = loc_res);
                    translate([disp_x-4/2-0.5+8, +28/2-2, 0])
                    cylinder(d = 4, h = 1, $fn = loc_res);
                }
                hull() {
                    translate([disp_x+disp_wid+4/2+0.5, -28/2+2, -1])
                    cylinder(d = 4, h = 2, $fn = loc_res);
                    translate([disp_x+disp_wid+4/2+0.5, +28/2-2, -1])
                    cylinder(d = 4, h = 2, $fn = loc_res);
                }
                hull() {
                    translate([disp_x+disp_wid+4/2+0.5, -28/2+2, 0])
                    cylinder(d = 4, h = 1, $fn = loc_res);
                    translate([disp_x+disp_wid+4/2+0.5-8, -28/2+2, 0])
                    cylinder(d = 4, h = 1, $fn = loc_res);
                }
                hull() {
                    translate([disp_x+disp_wid+4/2+0.5, +28/2-2, 0])
                    cylinder(d = 4, h = 1, $fn = loc_res);
                    translate([disp_x+disp_wid+4/2+0.5-8, +28/2-2, 0])
                    cylinder(d = 4, h = 1, $fn = loc_res);
                }
            }
            translate([0, 0, -15]) {
                hull() {
                    translate([-9, -14, 0])
                    cylinder(d = 2, h = 15, $fn = loc_res);
                    translate([-9, +14, 0])
                    cylinder(d = 2, h = 15, $fn = loc_res);
                }
                hull() {
                    translate([100-9, -14, 0])
                    cylinder(d = 2, h = 15, $fn = loc_res);
                    translate([100-9, +14, 0])
                    cylinder(d = 2, h = 15, $fn = loc_res);
                }
                hull() {
                    translate([-0, -18, 0])
                    cylinder(d = 2, h = 15, $fn = loc_res);
                    translate([100-15, -18, 0])
                    cylinder(d = 2, h = 15, $fn = loc_res);
                }
                hull() {
                    translate([-0, +18, 0])
                    cylinder(d = 2, h = 15, $fn = loc_res);
                    translate([100-15, +18, 0])
                    cylinder(d = 2, h = 15, $fn = loc_res);
                }
            }
        }
        // display cut out
        hull() {
            translate([disp_x, -28/2+4.5, -5])
            cylinder(d = 1, h = 10, $fn = loc_res);
            translate([disp_x, +28/2-4.5, -5])
            cylinder(d = 1, h = 10, $fn = loc_res);
            translate([disp_x+disp_wid, -28/2+4.5, -5])
            cylinder(d = 1, h = 10, $fn = loc_res);
            translate([disp_x+disp_wid, +28/2-4.5, -5])
            cylinder(d = 1, h = 10, $fn = loc_res);
        }
        // switch cut out
        hull() {
            translate([-6-1, -18/2, -5])
            cylinder(d = 1, h = 10, $fn = loc_res);
            translate([-6-1, +18/2-1, -5])
            cylinder(d = 1, h = 10, $fn = loc_res);
            translate([+6, -18/2, -5])
            cylinder(d = 1, h = 10, $fn = loc_res);
            translate([+6, +18/2-1, -5])
            cylinder(d = 1, h = 10, $fn = loc_res);
        }
        // m3 holes for senkkopf holz schraube
        translate([-15+3, -20+3, -2.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
        translate([-15+3, +20-3, -2.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
        translate([100-3, -20+3, -2.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
        translate([100-3, +20-3, -2.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
        
        // M2 holes for speaker
        translate([75, 0, -2])
        speaker2W_M2_Holes(6, loc_res);
        translate([75, 0, -2])
        speaker2W_Cover_Holes(6, loc_res);
    }
}

module partA(loc_res = 32) {
    difference() {
        cylinder(d = 5, h = 4, $fn = 4);
        translate([0, 0, -1])
        cylinder(d = 1.6, h = 6, $fn = loc_res);
    }
}

module partB(loc_res = 32) {
    //cylinder(d = 6, h = 13-2, $fn = loc_res);
    cube([16, 6, 11]);
}

//case1(0, 64);
//partA(); // 2 x
//translate([30, -16.5, -15]) 
partB(); // 4 x
