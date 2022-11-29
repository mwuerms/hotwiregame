/**
 * Martin Egli
 * 2021-12-04
 * parts for vibra alarm 2
 */

module battery() {
    color("Silver")
    translate([0, 0, 0])
    cube([40, 22, 9]);
    color("Yellow")
    translate([40, 0, 0])
    cube([6, 22, 5]);
}

module chargerPCB() {
    color("Silver")
    translate([-2, (19-8)/2, 1])
    cube([6, 8, 3]);
    color("Blue")
    translate([0, 0, 0])
    cube([25, 19, 2]);
}

module arduinoMicroProPCB() {
    color("Silver")
    for(n = [0:1:5]) {
        translate([-13, 1+2.54/2+n*2.54, 1.75])
        cube([14, 1, 1]);
    }
    color("Black")
    translate([-1, 1, 1])
    cube([2.5, 16, 2.5]);
    color("Black")
    translate([15, 9.5, 1])
    rotate([0, 0, -45])
    cube([8, 8, 2]);
    color("Blue")
    translate([0, 0, 0])
    cube([34, 19, 2]);
}

module displayPCB() {
    color("Blue")
    translate([0, 0, 0])
    cube([27, 28, 1]);
    color("White")
    translate([0, 4.5, 0])
    cube([27, 19, 1.5]);
}

module displayPCB2_25x27(loc_res = 32) {
    difference() {
        union() {
            color("Gray") // Black
            translate([0, 0, 0])
            cube([25, 27, 1]);
            color("White")
            translate([0, 5, 0])
            cube([25, 17, 1.5]);
            
            color("Silver") {
                translate([8.5, 27-1.7, -0.1])
                cylinder(d = 2, h = 1.2, $fn = loc_res);
                translate([8.5+1*2.54, 27-1.7, -0.1])
                cylinder(d = 2, h = 1.2, $fn = loc_res);
                translate([8.5+2*2.54, 27-1.7, -0.1])
                cylinder(d = 2, h = 1.2, $fn = loc_res);
                translate([8.5+3*2.54, 27-1.7, -0.1])
                cylinder(d = 2, h = 1.2, $fn = loc_res);
            }
        }
        // m3 holes
        translate([2, 2, -1])
        cylinder(d = 3, h = 4, $fn = loc_res);
        translate([25-2, 2, -1])
        cylinder(d = 3, h = 4, $fn = loc_res);
        translate([2, 27-2, -1])
        cylinder(d = 3, h = 4, $fn = loc_res);
        translate([25-2, 27-2, -1])
        cylinder(d = 3, h = 4, $fn = loc_res);
    }
}

module switch() {
    color("Gray")
    translate([0, 0, 0])
    cube([17, 13, 12]);
    color("Gray")
    translate([-2, -2, 12])
    cube([17+4, 13+4, 2]);
    color("Red")
    translate([1.5, 1.5, 14])
    rotate([0, 15, 0])
    cube([14, 10, 4]);
    color("Silver")
    translate([0.5, (13-5)/2,-7])
    cube([1, 5, 7]);
    color("Silver")
    translate([17/2-0.5, (13-5)/2,-7])
    cube([1, 5, 7]);
}

module vibraMotor() {
    color("Silver")
    cylinder(d = 10, h = 3, $fn = 32);
}

module speaker2W_M2_Holes(hi = 5, loc_res = 32) {
    translate([+(28/2-3), -(28/2-3), -1])
    cylinder(d = 2, h = hi, $fn = loc_res);
    translate([-(28/2-3), +(28/2-3), -1])
    cylinder(d = 2, h = hi, $fn = loc_res);
}

module speaker2W_Cover_Holes(hi = 5, loc_res = 32) {
    dia = 4;
    translate([0, 0, -1]) {
        translate([0, 0, 0])
        cylinder(d = dia, h = hi, $fn = loc_res);
        for(n = [0:1:5])
        translate([5*cos(n*60), 5*sin(n*60), 0])
        cylinder(d = dia, h = hi, $fn = loc_res);
        for(n = [0:1:5])
        translate([2*5*cos(n*60), 2*5*sin(n*60), 0])
        cylinder(d = dia, h = hi, $fn = loc_res);
        for(n = [0:1:5])
        translate([1.8*5*cos(n*60+30), 1.8*5*sin(n*60+30), 0])
        cylinder(d = dia, h = hi, $fn = loc_res);
    }
}

module speaker2W(loc_res = 32) {
    color("DarkGray")
    difference() {
        hull() {
            translate([+(28/2-1), +(28/2-1), -3])
            cylinder(r = 1, h = 3, $fn = loc_res);
            translate([+(28/2-1), -(28/2-1), -3])
            cylinder(r = 1, h = 3, $fn = loc_res);
            translate([-(28/2-1), +(28/2-1), -3])
            cylinder(r = 1, h = 3, $fn = loc_res);
            translate([-(28/2-1), -(28/2-1), -3])
            cylinder(r = 1, h = 3, $fn = loc_res);
        }
        translate([-(28/2), -(28/2), -4])
        cylinder(r = 3, h = 5, $fn = 4);
        translate([+(28/2), +(28/2), -4])
        cylinder(r = 3, h = 5, $fn = 4);
        translate([0, 0, -4])
        cylinder(d = 25, h = 5, $fn = loc_res);
        // M2 holes
        translate([0, 0, -3])
        speaker2W_M2_Holes(5, loc_res);
        
    }
    color("Silver")
    translate([0, 0, -11])
    cylinder(d = 23, h = 8, $fn = loc_res);
}

speaker2W();
speaker2W_Cover_Holes();