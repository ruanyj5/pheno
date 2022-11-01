% the using for Stacking Layer 
% making 46 images of one year become one image for phenoC++ input data type


clc
clear

Path_NDVI = './output/01_MOD09Q1_EVI2_sub/'; % input path (46 images) 
File_NDVI = dir([Path_NDVI,'*EVI2.tif']);
k=length(File_NDVI);

TileList=cell(k,1);

for i=1:k
    TileList(i)=cellstr(File_NDVI(i).name(9:12));    
end
TileList=unique(TileList); % get the year of the image
    
 
Path_NDVI8D = './output/08_MOD09A1_EVI8D/'; %output path (one image)  

mkdir(Path_NDVI8D);



for I_Tile=1:numel(TileList)

tic
    
    TileName = TileList{I_Tile};

    
    File_MOD09NDVI8D = dir([Path_NDVI,'*',TileName,'*EVI2.tif']);
    

    if numel(File_MOD09NDVI8D)~=46
       disp(['File numbers are not correct! ',TileName,' ',num2str(numel(File_MOD09NDVI8D))]);
    end

    
    % read data
    [A,R]= geotiffread([File_MOD09NDVI8D(1).folder,'/',File_MOD09NDVI8D(1).name]);
     Proj = geotiffinfo([File_MOD09NDVI8D(1).folder,'/',File_MOD09NDVI8D(1).name]);
    
    MOD098NDVI = nan([R.RasterSize 46]);
   
        
    for I_File=1:numel(File_MOD09NDVI8D)
        
        
        MOD098NDVI(:,:,I_File)=geotiffread([File_MOD09NDVI8D(I_File).folder,'/',File_MOD09NDVI8D(I_File).name]);
        
    end
    

    MOD098NDVI = reshape(MOD098NDVI,[],46)';    
    MOD098NDVI = double(MOD098NDVI)/10000; % get double data

    

 
    % remove and fill outlier pixels
    MOD098TMP = MOD098NDVI;
    
    MOD098BND = MOD098TMP>-1 | MOD098TMP<1;
    MOD098FILL=(MOD098TMP==0);
    MOD098MSK = ~(MOD098FILL & MOD098BND);
     
    
    % divide data into multiple blocks
    Step = int32(R.RasterSize(1)*R.RasterSize(2)/50);
    Step_list=1:Step:R.RasterSize(1)*R.RasterSize(2);
    
    
    % 
    tic
    
    for i=1:length(Step_list)
        
        
        I_Data=Step_list(i);
        
        Pos=min(I_Data+Step-1,R.RasterSize(1)*R.RasterSize(2));
        Block8DNDVI=MOD098NDVI(:,I_Data:Pos);
        Block8DMSK=MOD098MSK(:,I_Data:Pos);
        Block8DNDVI(~Block8DMSK) = nan;
        

        
        MOD098HAM = hampel(Block8DNDVI);      
        MOD098SGF = sgolayfilt(MOD098HAM,3,11); % using sgolayfilt 
        
        
        
        %
        MOD098TMP(:,I_Data:Pos)=MOD098SGF;
        
        
             
    end
    toc
	
	% clear 
	clear MOD098NDVI;
    clear MOD098BND;
    clear MOD098FILL;
    clear MOD098MSK;
	
	MOD098TMP=int16(MOD098TMP*10000);
    MOD098SGF_NDVI = reshape(MOD098TMP',R.RasterSize(1),R.RasterSize(2),[]);   

    warning('off'); 
    clear MOD098TMP;
    

    % out put image
    geotiffwrite([Path_NDVI8D,File_MOD09NDVI8D(1).name(1:end-4),'_8DSGF_EVI.tif'],int16(MOD098SGF_NDVI),R,...
        'TiffType','bigtiff');   

    disp(['Done with ',I_Tile,':',TileName]);
    toc
    
    clear MOD098SGF_NDVI;  
    
end
