ld distance(Pt p, Cir c) { 
    return max(0.L, (p - c).length() - c.r); 
}