function simulacao = respostas(experimento)
% 0.17 tempo de subida
tf = 10;
xr.signals.dimensions = 1;
yr.signals.dimensions = 1;
zr.signals.dimensions = 1;
psir.signals.dimensions = 1;

if strcmp(experimento, 'zstep')
    xr.time = [0; tf];
    xr.signals.values = [0; 0];
    yr.time = [0; tf];
    yr.signals.values = [0; 0];
    zr.time = [0; tf];
    zr.signals.values = [1; 1];
    psir.time = [0.0; tf];
    psir.signals.values = [0; 0];
elseif strcmp(experimento, 'ystep')
    xr.time = [0; tf];
    xr.signals.values = [0; 0];
    yr.time = [0; tf];
    yr.signals.values = [1; 1];
    zr.time = [0; tf];
    zr.signals.values = [0; 0];
    psir.time = [0.0; tf];
    psir.signals.values = [0; 0];
elseif strcmp(experimento, 'xstep')
    xr.time = [0; tf];
    xr.signals.values = [1; 1];
    yr.time = [0; tf];
    yr.signals.values = [0; 0];
    zr.time = [0; tf];
    zr.signals.values = [0; 0];
    psir.time = [0.0; tf];
    psir.signals.values = [0; 0];
elseif strcmp(experimento, 'psistep')
    tf = 1;
    xr.time = [0; tf];
    xr.signals.values = [0; 0];
    yr.time = [0; tf];
    yr.signals.values = [0; 0];
    zr.time = [0; tf];
    zr.signals.values = [0; 0];
    psir.time = [0.0; tf];
    psir.signals.values = [1; 1];
elseif strcmp(experimento, 'yramp')
    xr.time = [0; tf];
    xr.signals.values = [0; 0];
    yr.time = [0; tf];
    yr.signals.values = [0; tf];
    zr.time = [0; tf];
    zr.signals.values = [0; 0];
    psir.time = [0.0; tf];
    psir.signals.values = [0; 0];
elseif strcmp(experimento, 'zramp')
    xr.time = [0; tf];
    xr.signals.values = [0; 0];
    yr.time = [0; tf];
    yr.signals.values = [0; 0];
    zr.time = [0; tf];
    zr.signals.values = [0; tf];
    psir.time = [0.0; tf];
    psir.signals.values = [0; 0];
elseif strcmp(experimento, 'yhighstep')
    tf = 3;
    xr.time = [0; tf];
    xr.signals.values = [0; 0];
    yr.time = [0; tf];
    yr.signals.values = [2; 2];
    zr.time = [0; tf];
    zr.signals.values = [0; 0];
    psir.time = [0.0; tf];
    psir.signals.values = [0; 0];
elseif strcmp(experimento, 'xhighstep')
    tf = 3;
    xr.time = [0; tf];
    xr.signals.values = [2.2; 2.2];
    yr.time = [0; tf];
    yr.signals.values = [0; 0];
    zr.time = [0; tf];
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