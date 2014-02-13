x=load('pfteststate.txt');
X=load('pftestesti.txt');

coor=1:size(x,1);
for i=1:4
    figure(i);
    hold on;
    plot(coor,x(:,i),'r');
    plot(coor,X(:,i),'g');
end