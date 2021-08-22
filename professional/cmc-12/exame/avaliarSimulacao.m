function avaliarSimulacao(sim)
    figure; hold on;
    plot3(sim.x.Data, sim.y.Data, sim.z.Data);
    grid on
    xlabel('x'); ylabel('y'); zlabel('z');
    
    hold off
    
%     figure 
%     plot(sim.x.Data, sim.y.Data)
%     xlabel('x')
%     ylabel('y')
%     
%     figure;
%     plot(sim.y.Data, sim.z.Data)
%     xlabel('y')
%     ylabel('z')
%     
%     figure;
%     plot(sim.x.Data, sim.z.Data)
%     xlabel('x')
%     ylabel('z')

    figure;
    plot(sim.x.Time, sim.x.Data)
    hold on
    plot(sim.xr.Time, sim.xr.Data, '--')
    title('x')
    grid minor
    hold off
    
    figure;
    plot(sim.y.Time, sim.y.Data)
    hold on
    plot(sim.yr.Time, sim.yr.Data, '--')
    xlabel('Tempo (s)')
    ylabel('y (m)')
    title('Com windup')
    grid minor
    hold off
    
    figure;
    plot(sim.z.Time, sim.z.Data)
    hold on
    plot(sim.zr.Time, sim.zr.Data, '--')
    xlabel('Tempo (s)')
    ylabel('z (m)')
    title('Resposta ao degrau')
    grid minor
    hold off
    
    figure;
    plot(sim.psi.Time, sim.psi.Data)
    hold on
    plot(sim.psir.Time, sim.psir.Data, '--')
    title('psi')
    grid minor
    hold off;
    
      figure;
    plot(sim.theta.Time, sim.theta.Data)
    hold on
    plot(sim.theta_r.Time, sim.theta_r.Data, '--')
    title('theta')
    grid minor
    hold off;
    
    figure;
    plot(sim.phi.Time, sim.phi.Data)
    hold on
    plot(sim.phi_r.Time, sim.phi_r.Data, '--')
    legend('observado', 'referência')
    title('Efeito da saturação')
    xlabel('Tempo (s)')
    ylabel('Guinada (rad/s)')
    grid minor
    hold off;
end