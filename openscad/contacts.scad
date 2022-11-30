/**
 * Martin Egli
 * 2021-12-04
 * 3d parts for hot wire game, wire contacts
 */
 
use <parts.scad>

module endcontacts(loc_res = 32) {
    difference() {
        translate([0, 0, 0])
        cylinder(d = 25, h= 1, $fn = loc_res);
        
        translate([4, 0, -1])
        cylinder(d = 2, h= 3, $fn = loc_res);
        translate([0, 0, -1])
        cylinder(d = 8, h= 3, $fn = loc_res);
    }
}

module wireholder(loc_res = 32) {
    difference() {
        union() {
            hull() {
            translate([0, 0, 1])
            cylinder(d = 12, h= 1, $fn = loc_res);
            //translate([0, 0, 2])
            //cylinder(d1 = 12, d2 = 3.85, h= 10, $fn = loc_res);
            translate([0, 0, 11.5])
            sphere(d = 4, $fn = loc_res);
            }
            translate([0, 0, -10])
            cylinder(d = 8, h= 13, $fn = loc_res);
        }
        #hull() {
            translate([4, 0, -11])
            sphere(d = 2, $fn = loc_res);
            translate([4, 0, 1])
            sphere(d = 2, $fn = loc_res);
            translate([10, 0, 1])
            sphere(d = 2, $fn = loc_res);
        }
        translate([0, 0, -11])
        cylinder(d = 2, h= 25, $fn = loc_res);
    }
}

module handcap_top(loc_res = 32) {
    difference() {
        union() {
            hull() {
                translate([0, 0, 1])
                cylinder(d = 25, h= 1, $fn = loc_res);
                translate([0, 0, 11.5])
                sphere(d = 12, $fn = loc_res);
            }
            translate([0, 0, -10])
            cylinder(d = 8, h= 13, $fn = loc_res);
        }
        hull() {
            translate([+1, 0, -11])
            cylinder(d = 2, h= 50, $fn = loc_res);
            translate([-1, 0, -11])
            cylinder(d = 2, h= 50, $fn = loc_res);
        }
    }
}

module handcap_bot(loc_res = 32) {
    difference() {
        union() {
            hull() {
                translate([0, 0, 0])
                cylinder(d = 25, h= 1, $fn = loc_res);
                translate([0, 0, 10])
                sphere(d = 20, $fn = loc_res);
            }
            translate([0, 0, -10])
            cylinder(d = 8, h= 13, $fn = loc_res);
        }
        translate([0, 0, -11])
        cylinder(d = 2, h= 50, $fn = loc_res);
    }
}

//endcontacts(64); // 2 x
//wireholder(64); // 2 x
//handcap_top(64); // 1 x
handcap_bot(64); // 1 x
