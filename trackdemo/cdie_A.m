function [A] = cdie_A(q1,q2)
%计算重叠面积
%   Detailed explanation goes here
%   q1(1)=x1 q1(2)=y1
%   q1(3)=x2 q1(4)=y2
%temp =zeros(2,4);
if((((q1(1)-q2(3))*(q1(3)-q2(1)))<=0)&&(((q1(2)-q2(4))*(q1(4)-q2(2))<=0)))
    temp1=sort([q1(1),q1(3),q2(1),q2(3)]);
    temp2=sort([q1(2),q1(4),q2(2),q2(4)]);
    A=(temp1(3)-temp1(2))*(temp2(3)-temp2(2));
else
    A=0;    
end
end

