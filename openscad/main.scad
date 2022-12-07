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

module partC(loc_res = 32) {
    difference() {
        union() {
            hull() {
                translate([-60,  3, 0])
                cylinder(d = 2*3, h = 1, $fn = loc_res);
                translate([+60,  3, 0])
                cylinder(d = 2*3, h = 1, $fn = loc_res);
                translate([-60,  80, 0])
                cylinder(d = 2*3, h = 1, $fn = loc_res);
                translate([+60,  80, 0])
                cylinder(d = 2*3, h = 1, $fn = loc_res);
            }
            hull() {
                translate([-20,  1, -2])
                cylinder(d = 2, h = 3, $fn = loc_res);
                translate([-20, 30, -2])
                cylinder(d = 2, h = 3, $fn = loc_res);
            }
            hull() {
                translate([+20,  1, -2])
                cylinder(d = 2, h = 3, $fn = loc_res);
                translate([+20, 30, -2])
                cylinder(d = 2, h = 3, $fn = loc_res);
            }
            hull() {
                translate([-20, 75, -2])
                cylinder(d = 2, h = 3, $fn = loc_res);
                translate([+20, 75, -2])
                cylinder(d = 2, h = 3, $fn = loc_res);
            }
        }
        // m3 holes for senkkopf holz schraube
        translate([+(60-2), 5, -1.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
        translate([-(60-2), 5, -1.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
        translate([+(60-2), 80-2, -1.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
        translate([-(60-2), 80-2, -1.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
    }
}

module textSingenderDraht(loc_res = 32) {
    difference() {
        hull() {
            translate([5+3, 5+3, 0])
            cylinder(d = 16, h = 2, $fn = loc_res);
            translate([121, 5+3, 0])
            cylinder(d = 16, h = 2, $fn = loc_res);
        }
        translate([15, 4, -1])
        //scale([1.25,1.5,1])
        linear_extrude(4)
        text("Singender Draht");
        // m3 holes for senkkopf holz schraube
        translate([5+3, 5+3, -0.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
        translate([121, 5+3, -0.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
    }
    // g
    translate([35, 6.5, 0])
    cube([7, 2, 1]);
    // e
    translate([45.25, 6.5, 0])
    cube([1.5, 7, 1]);
    // d
    translate([57, 6.5, 0])
    cube([8, 2, 1]);
    // e
    translate([68, 6.5, 0])
    cube([1.5, 7, 1]);
    // D
    translate([80.5, 7.5, 0])
    cube([10, 2, 1]);
    // a
    translate([97.75, 2, 0])
    cube([1.5, 7, 1]);
}
module textStart(loc_res = 32) {
    difference() {
        hull() {
            translate([5+3, 5+3, 0])
            cylinder(d = 16, h = 2, $fn = loc_res);
            translate([51, 5+3, 0])
            cylinder(d = 16, h = 2, $fn = loc_res);
        }
        translate([15, 3.5, -1])
        linear_extrude(4)
        text("Start");
        // m3 holes for senkkopf holz schraube
        translate([5+3, 5+3, -0.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
        translate([51, 5+3, -0.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
    }
    // a
    translate([31, 2, 0])
    cube([1.5, 7, 1]);
}
module textZiel(loc_res = 32) {
    difference() {
        hull() {
            translate([5+3, 5+3, 0])
            cylinder(d = 16, h = 2, $fn = loc_res);
            translate([44, 5+3, 0])
            cylinder(d = 16, h = 2, $fn = loc_res);
        }
        translate([15, 3.5, -1])
        linear_extrude(4)
        text("Ziel");
        // m3 holes for senkkopf holz schraube
        translate([5+3, 5+3, -0.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
        translate([44, 5+3, -0.5])
        cylinder(d2 = 6.5, d1 = 2.5, h = 3, $fn = loc_res);
    }
    // e
    translate([29.25, 6.5, 0])
    cube([1.5, 7, 1]);
}

//case1(0, 64);
//partA(); // 2 x
//translate([30, -16.5, -15]) 
//partB(); // 4 x
//partC(); // 1 x

//textSingenderDraht();
//textStart();
//textZiel();
