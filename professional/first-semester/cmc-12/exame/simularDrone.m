function simulacao = simularDrone(experimento)

tf = 10;
xr.signals.dimensions = 1;
yr.signals.dimensions = 1;
zr.signals.dimensions = 1;
psir.signals.dimensions = 1;

if strcmp(experimento, 'sela')
    tf = 30;
    xr.time = [0; tf/8; 2*tf/8; 3*tf/8; 4*tf/8; 5*tf/8; 6*tf/8; 7*tf/8; tf];
    xr.signals.values = [0; 0; 0; 0; 1; 1; 1; 1; 0];
    yr.time = [0; tf/8; 2*tf/8; 3*tf/8; 4*tf/8; 5*tf/8; 6*tf/8; 7*tf/8; tf];
    yr.signals.values = [0; 0; 1; 1; 1; 1; 0; 0; 0];
    zr.time = [0; tf/8; 2*tf/8; 3*tf/8; 4*tf/8; 5*tf/8; 6*tf/8; 7*tf/8; tf];
    zr.signals.values = [0; 1; 1; 0; 0; 1; 1; 0; 0];
    psir.time = [0; tf/8; 2*tf/8; 3*tf/8; 4*tf/8; 5*tf/8; 6*tf/8; 7*tf/8; tf];
    psir.signals.values = [0; 0; 0; 0; 0; 0; 0; 0; 0];
elseif strcmp(experimento, 'quadrado')
    tf = 10;
    xr.time = [0; tf/4; tf/2; 3*tf/4; tf; 2*tf];
    xr.signals.values = [0; 0; 5; 5; 0; 0];
    yr.time = [0; tf/4; tf/2; 3*tf/4; tf; 2*tf];
    yr.signals.values = [0; 5; 5; 0; 0; 0];
    zr.time = [0; tf/4; tf/2; 3*tf/4; tf; 2*tf];
    zr.signals.values = [0; 5; 5; 0; 0; 5];
    psir.time = [0; tf/4; tf/2; 3*tf/4; tf; 2*tf];
    psir.signals.values = [0; 0; 0; 0; 0; 0];
elseif strcmp(experimento, 'espiral')
    dt = 1e-3;
    amplitude = 10.0;
    omega = 0.5;
    tf = 20.0;
    t = (0:dt:tf)';
    xr.time = t;
    xr.signals.values = amplitude*sin(omega*t);
    yr.time = t;
    yr.signals.values = amplitude*cos(omega*t) - amplitude;
    zr.time = [0.0; tf];
    zr.signals.values = [0; 2];
    psir.time = [0.0; tf];
    psir.signals.values = [0; 0];
elseif strcmp(experimento, 'bicone')
    dt = 1e-3;
    amp = 0.1;
    omega = 0.5;
    tf = 200.0;
    t = linspace(0, tf, 20000)';
    amplitude = vertcat(linspace(0, amp, 10000)', linspace(amp, 0, 10000)');
    xr.time = t;
    xr.signals.values = amplitude.*sin(omega*t);
    yr.time = t;
    yr.signals.values = amplitude.*cos(omega*t);
    zr.time = [0.0; tf];
    zr.signals.values = [0; 2];
    psir.time = [0.0; tf];
    psir.signals.values = [0; 0];
elseif strcmp(experimento, 'lissajous')
    dt = 1e-3;
    amplitude = 1.0;
    omegaX = 1/9;
    omegaY = 1/10;
    
    tf = 200.0;
    t = (0:dt:tf)';
    xr.time = t;
    xr.signals.values = amplitude*sin(omegaX*t);
    yr.time = t;
    yr.signals.values = amplitude*cos(omegaY*t) - amplitude;
    zr.time = [0.0; tf];
    zr.signals.values = [0; 0];
    psir.time = [0.0; tf];
    psir.signals.values = [0; 0];
end

    planta = obterPlanta();
    proj = obterProjeto();
    
    assignin('base', 'planta', planta);
    assignin('base', 'proj', proj);
    assignin('base', 'xr', xr);
    assignin('base', 'yr', yr);
    assignin('base', 'zr', zr);
    assignin('base', 'psir', psir);
    
    load_system('drone');
    
    set_param('drone', 'StopTime', sprintf('%g', tf));

    simulacao = sim('drone');
    avaliarSimulacao(simulacao);
end
