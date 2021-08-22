multifractal = load("data/solar_wind1b.dat");
X=cumsum(multifractal-mean(multifractal));
X=transpose(X);
scale=[16,32,64,128,256,512,1024];
q=-10:1:10;
m=1;

for ns=1:length(scale)
    segments(ns)=floor(length(X)/scale(ns));
    for v=1:segments(ns)
        Index=((((v-1)*scale(ns))+1):(v*scale(ns)));
        C=polyfit(Index,X(Index),m);
        fit=polyval(C,Index);
        RMS{ns}(v)=sqrt(mean((X(Index)-fit).^2));
    end
    for nq=1:length(q)
        qRMS{nq,ns}=RMS{ns}.^q(nq);
        Fq(nq,ns)=mean(qRMS{nq,ns}).^(1/q(nq));
    end
    Fq(q==0,ns)=exp(0.5*mean(log(RMS{ns}.^2)));
end

for nq=1:length(q)
    C=polyfit(log2(scale),log2(Fq(nq,:)),1);
    Hq(nq)=C(1);
    qRegLine{nq}=polyval(C,log2(scale));
end

figure;
plot(q, Hq, '-o');
print("-dpng", "figures/generalized_hurst1b.png");

tq=Hq.*q-1;
figure;
plot(q, tq, '-o');
print("-dpng", "figures/multifractal_scal_exp1b.png");

hq=diff(tq)./(q(2)-q(1));
Dq=(q(1:end-1).*hq)-tq(1:end-1);
figure;
plot(hq, Dq, '-o');
print("-dpng", "figures/multifractal_spectrum1b.png");

clear;

multifractal = load("data/solar_wind2.dat");
X=cumsum(multifractal-mean(multifractal));
X=transpose(X);
scale=[16,32,64,128,256,512,1024];
q=-10:1:10;
m=1;

for ns=1:length(scale)
    segments(ns)=floor(length(X)/scale(ns));
    for v=1:segments(ns)
        Index=((((v-1)*scale(ns))+1):(v*scale(ns)));
        C=polyfit(Index,X(Index),m);
        fit=polyval(C,Index);
        RMS{ns}(v)=sqrt(mean((X(Index)-fit).^2));
    end
    for nq=1:length(q)
        qRMS{nq,ns}=RMS{ns}.^q(nq);
        Fq(nq,ns)=mean(qRMS{nq,ns}).^(1/q(nq));
    end
    Fq(q==0,ns)=exp(0.5*mean(log(RMS{ns}.^2)));
end

for nq=1:length(q)
    C=polyfit(log2(scale),log2(Fq(nq,:)),1);
    Hq(nq)=C(1);
    qRegLine{nq}=polyval(C,log2(scale));
end

figure;
plot(q, Hq, '-o');
print("-dpng", "figures/generalized_hurst2.png");

tq=Hq.*q-1;
figure;
plot(q, tq, '-o');
print("-dpng", "figures/multifractal_scal_exp2.png");

hq=diff(tq)./(q(2)-q(1));
Dq=(q(1:end-1).*hq)-tq(1:end-1);
figure;
plot(hq, Dq, '-o');
print("-dpng", "figures/multifractal_spectrum2.png");