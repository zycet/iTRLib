%读取txt文件中的数据，并进行比较分析
%

car_gt=load('car\gt.txt');
car_gt_int=floor(car_gt(:,:));
car_mtfb=load('car\mtfb.txt');
car_mtfbkf=load('car\mtfbkf.txt');
car_mtfbncckf=load('car\mtfbncckf.txt');
car_mtkf=load('car\mtkf.txt');

david_gt=load('david\gt.txt');
david_gt_int=floor(david_gt(:,:));
david_result=load('david\result.txt');

%A_car_mtfb : 1 gt面积，2 mtfb面积，3 重叠面积 4 重叠率
A_car_mtfb=zeros(size(car_mtfb,1),4);
for i = 1: size(car_mtfb,1)
    if (car_gt_int(i,1)~='Nan')
        A_car_mtfb(i,1) =(car_gt_int(i,3)-car_gt_int(i,1))*(car_gt_int(i,4)-car_gt_int(i,2));
        A_car_mtfb(i,2) =(car_mtfb(i,3)-car_mtfb(i,1))*(car_mtfb(i,4)-car_mtfb(i,2));
        A_car_mtfb(i,3) =cdie_A(car_gt_int(i,:),car_mtfb(i,:));
        A_car_mtfb(i,4) =A_car_mtfb(i,3)/(A_car_mtfb(i,1)+A_car_mtfb(i,2)-A_car_mtfb(i,3));
    else
        A_car_mtfb(i,:)='Nan';
    end
end
%A_car_mtkf : 1 gt面积，2 mtkf面积，3 重叠面积 4 重叠率
A_car_mtkf=zeros(size(car_mtkf,1),4);
for i = 1: size(car_mtkf,1)
    if (car_gt_int(i,1)~='Nan')
        A_car_mtkf(i,1) =(car_gt_int(i,3)-car_gt_int(i,1))*(car_gt_int(i,4)-car_gt_int(i,2));
        A_car_mtkf(i,2) =(car_mtkf(i,3)-car_mtkf(i,1))*(car_mtkf(i,4)-car_mtkf(i,2));
        A_car_mtkf(i,3) =cdie_A(car_gt_int(i,:),car_mtkf(i,:));
        A_car_mtkf(i,4) =A_car_mtkf(i,3)/(A_car_mtkf(i,1)+A_car_mtkf(i,2)-A_car_mtkf(i,3));
    else
        A_car_mtkf(i,:)='Nan';
    end
end
%A_car_mtfbkf : 1 gt面积，2 mtfbkf面积，3 重叠面积 4 重叠率
A_car_mtfbkf=zeros(size(car_mtfbkf,1),4);
for i = 1: size(car_mtfbkf,1)
    if (car_gt_int(i,1)~='Nan')
        A_car_mtfbkf(i,1) =(car_gt_int(i,3)-car_gt_int(i,1))*(car_gt_int(i,4)-car_gt_int(i,2));
        A_car_mtfbkf(i,2) =(car_mtfbkf(i,3)-car_mtfbkf(i,1))*(car_mtfbkf(i,4)-car_mtfbkf(i,2));
        A_car_mtfbkf(i,3) =cdie_A(car_gt_int(i,:),car_mtfbkf(i,:));
        A_car_mtfbkf(i,4) =A_car_mtfbkf(i,3)/(A_car_mtfbkf(i,1)+A_car_mtfbkf(i,2)-A_car_mtfbkf(i,3));
    else
        A_car_mtfbkf(i,:)='Nan';
    end
end
%A_car_mtfbncckf : 1 gt面积，2 mtfbncckf面积，3 重叠面积 4 重叠率
A_car_mtfbncckf=zeros(size(car_mtfbncckf,1),4);
for i = 1: size(car_mtfbncckf,1)
    if (car_gt_int(i,1)~='Nan')
        A_car_mtfbncckf(i,1) =(car_gt_int(i,3)-car_gt_int(i,1))*(car_gt_int(i,4)-car_gt_int(i,2));
        A_car_mtfbncckf(i,2) =(car_mtfbncckf(i,3)-car_mtfbncckf(i,1))*(car_mtfbncckf(i,4)-car_mtfbncckf(i,2));
        A_car_mtfbncckf(i,3) =cdie_A(car_gt_int(i,:),car_mtfbncckf(i,:));
        A_car_mtfbncckf(i,4) =A_car_mtfbncckf(i,3)/(A_car_mtfbncckf(i,1)+A_car_mtfbncckf(i,2)-A_car_mtfbncckf(i,3));
    else
        A_car_mtfbncckf(i,:)='Nan';
    end
end


%A_david_result : 1 gt面积，2 mtfb面积，3 重叠面积 4 重叠率
A_david_result=zeros(size(david_result,1),4);
for i = 1: size(david_result,1)
    if (david_gt_int(i,1)~='Nan')
        A_david_result(i,1) =(david_gt_int(i,3)-david_gt_int(i,1))*(david_gt_int(i,4)-david_gt_int(i,2));
        A_david_result(i,2) =(david_result(i,3)-david_result(i,1))*(david_result(i,4)-david_result(i,2));
        A_david_result(i,3) =cdie_A(david_gt_int(i,:),david_result(i,:));
        A_david_result(i,4) =A_david_result(i,3)/(A_david_result(i,1)+A_david_result(i,2)-A_david_result(i,3));
    else
        A_david_result(i,:)=2;
    end
end
figure('NumberTitle','off','Name','car');
subplot(4,1,1);
plot(A_car_mtfb(:,4),'b');
xlabel('times');
ylabel('mtfb');
subplot(4,1,2);
plot(A_car_mtfbkf(:,4),'b');
xlabel('times');
ylabel('mtfbkf');
subplot(4,1,3);
plot(A_car_mtfbncckf(:,4),'b');
xlabel('times');
ylabel('mtfbncckf');
subplot(4,1,4);
plot(A_car_mtkf(:,4),'b');
xlabel('times');
ylabel('mtkf');
figure('NumberTitle','off','Name','david');
%subplot(1,1,1);
plot(A_david_result(:,4),'b');
xlabel('times');
ylabel('david_result');
