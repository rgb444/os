#include <stdio.h>
int optimal(int pages[],int page_size,int frames[],int frame_size,int currindex)
{
    int found = 0;
    int farthest = -1;
    int pos = 0;
    for(int i=0;i<frame_size;i++){
        found=0;
        for(int j=currindex+1;j<page_size;j++){
            if(pages[j]==frames[i]){
                found=1;
                if(farthest<j){
                    farthest=j;
                    pos = i;
                }
                  break;
            }
        }
        if(found==0){
            return i;
        }
        
    }
    return pos;
}

int main()
{   
    int frame_size,page_size;
    printf("Enter the size of the frames : ");
    scanf("%d",&frame_size);
    
    printf("Enter pages size : ");
    scanf("%d",&page_size);
    
    int pages[page_size],frames[frame_size];
    for(int i=0;i<frame_size;i++){
        frames[i]=-1;
    }
    
    
    printf("Enter pages : ");
    for(int i=0;i<page_size;i++){
        scanf("%d",&pages[i]);
    }
    
    
    printf("\n\n");
    int flag1,flag2,pos,hit=0,fault=0;
    
    for(int i=0;i<page_size;i++){
        flag1=0,flag2=0,pos;
    
        for(int j=0;j<frame_size;j++){
            if(frames[j]==pages[i]){
                flag1=flag2=1;
                hit++;
                break;
            }
        }
        
        if(flag1==0){
            for(int j=0;j<frame_size;j++){
                if(frames[j]==-1){
                    frames[j]=pages[i];
                    flag2=1;
                    fault++;
                    break;
                }
            }
        }
        
        if(flag2==0){
            pos = optimal(pages,page_size,frames,frame_size,i);
            frames[pos]=pages[i];
            fault++;
        }
        
        printf("At %d page frame is:",pages[i]);
        for(int j=0;j<frame_size;j++){
            if(frames[j]!=-1)
            printf("%d ",frames[j]);
        }
        printf("\n");
        
        
    }
    
    printf("Total age fault is %d \n",fault);
    printf("Total Page hit is %d \n",hit);

    return 0;
}
