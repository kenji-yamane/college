function proj = obterProjeto()
    planta = obterPlanta();
    req = obterRequisitos();
    
    proj.Kd_theta = 2*req.xi_theta*req.wn_theta*planta.Iy;
    proj.Kp_theta = planta.Iy*req.wn_theta^2;
    
    proj.Kd_phi = 2*req.xi_phi*req.wn_phi*planta.Ix;
    proj.Kp_phi = planta.Ix*req.wn_phi^2;
    
    proj.Kd_psi = 2*req.xi_psi*req.wn_psi*planta.Iz;
    proj.Kp_psi = planta.Iz*req.wn_psi^2;
    
    proj.Kd_x = 7*req.wn_x*req.xi_x;
    proj.Kp_x = 10*req.wn_x^2*req.xi_x^2 + req.wn_x^2;
    proj.Ki_x = 5*req.wn_x^3*req.xi_x;
    
    proj.Kd_y = 7*req.wn_y*req.xi_y;
    proj.Kp_y = 10*req.wn_y^2*req.xi_y^2 + req.wn_y^2;
    proj.Ki_y = 5*req.wn_y^3*req.xi_y;
    
    proj.Kd_z = -planta.m*7*req.wn_z*req.xi_z;
    proj.Kp_z = -planta.m*10*req.wn_z^2*req.xi_z^2 + req.wn_z^2;
    proj.Ki_z = -planta.m*5*req.wn_z^3*req.xi_z;

end