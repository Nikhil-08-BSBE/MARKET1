#include<iostream>
using namespace std;
struct term{long long int company_id; long long int price;};
struct node{long long int left_height;long long int right_height;long long int company_id;long long int price; node *left_link;node *right_link; long long int published_price;};
node *n,*temp,*start,*n1,*n2,*n3,*n4,*n5,*n6;
//to pass the node without use
node *goodnode()
{
    node *good;
    good=new node;
    good->left_height=0;
    good->right_height=0;
    return good;
}
//to modify the height of parent "A" whose child "B" can be on right or left
void height_modification(node *A,node *B)
{
    if(A->left_link==B)
    {
        if(B!=NULL)
        {
            if(B->left_height > B->right_height)
             {
                A->left_height=B->left_height+1;
             }
            else
            {
                A->left_height=B->right_height+1;
            }
        }
        else
        {
            A->left_height=0;
        }
    }
    if(A->right_link==B)
    {
        if(B!=NULL)
        {
            if(B->left_height > B->right_height)
            {
                A->right_height=B->left_height+1;
            }
            else
            {
                A->right_height=B->right_height+1;
            }
        }
        else
        {
            A->right_height=0;
        }
    }
}
//to find the difference of left height and right height
int height(node *A)
{
    return A->left_height-A->right_height;
}
//to find due to which child rotation is going to happen
node *to_find_B(node *A)
{
        if(height(A)>1)
        {
            return A->left_link;
        }
        else
        {
            return A->right_link;
        }
}
//to change the parent link while deleting
void parent_linking(node *parent,node *A,node *B)
{
    if(parent!=A)
        {
            if(parent->left_link==A)
            {
                parent->left_link=B;
            }
            else
            {
                parent->right_link=B;
            }
        }
}
//first entry of register company of initial stock
void first_node(term arr[],long long int no_of_initial_data)
{
    n=new node;
    n->company_id=arr[no_of_initial_data/2].company_id;
    n->price=arr[no_of_initial_data/2].price;
    n->left_height=0;
    n->right_height=0;
    n->published_price=arr[no_of_initial_data/2].price;
    temp=n; start=n;
}
//to find the node whose price has to update if found
node *traverse(long long int company_id)
{
    while(temp->company_id !=company_id)
    {
        if(temp->company_id < company_id and temp->right_link!=NULL)
        {
            temp=temp->right_link;
        }
        else if(temp->company_id > company_id and temp->left_link!=NULL)
        {
            temp=temp->left_link;
        }
        else
        {
            break;
        }
    }
    return temp;
}
//avl tree of initial stock
int  avltree_of_initial_stock(term arr[],long long int start, long long int mid,long long int end,long long int no_of_initial_data,node *temp,node *n,node *n1,node *n2)
{
    long long int mid1,mid2;
    if(start>=end)
    {
        return 0;
    }
    else
    {
        mid1=(start+mid-1)/2;
        mid2=(mid+1+end)/2;
        if(mid1>=0 and start!=mid)
        {
            n1=new node;
            n1->company_id=arr[mid1].company_id;
            n1->price=arr[mid1].price;
            n1->left_height=0;
            n1->right_height=0;
            n1->published_price=arr[mid1].price;
            temp->left_link=n1;
            temp->left_height++;
        }
        if(mid2>=0)
        {
            n2=new node;
            n2->company_id=arr[mid2].company_id;
            n2->price=arr[mid2].price;
            n2->left_height=0;
            n2->right_height=0;
            n2->published_price=arr[mid2].price;
            temp->right_link=n2;
            temp->right_height++;
        }
        avltree_of_initial_stock(arr,start,mid1,mid-1,no_of_initial_data,n1,n1,n1,n2);
        if(end!=(no_of_initial_data-1)/2)
        {
            avltree_of_initial_stock(arr,mid+1,mid2,end,no_of_initial_data,n2,n2,n1,n2);
        }
        if(n!=n1){height_modification(n,n1);}
        if(n!=n2){height_modification(n,n2);}
    }
    return 0;
}
//to print tree(just for debugging)
int print_tree(node *temp)
{
    if(temp->left_link==NULL and temp->right_link==NULL)
    {
        cout<<"temp_company_id:"<<temp->company_id<<" temp->left_height:"<<temp->left_height
    <<" temp->right_height:"<<temp->right_height<<endl;
        return 0;
    }
    else
    {
cout<<"temp_company_id:"<<temp->company_id<<" temp->left_height:"<<temp->left_height
    <<" temp->right_height:"<<temp->right_height<<endl;
        if(temp->left_link!=NULL )print_tree(temp->left_link);
        if(temp->right_link!=NULL )print_tree(temp->right_link);
        return 0;
    }
}
//merge sort
void merge(term arr[],long long int left,long long int mid,long long int right )
{
    long long int mid1=mid-left+1;
    long long int mid2=right-mid;
    term left_arr[mid1];
    term right_arr[mid2];
    for(long long int i=0;i<mid1;i++)
    {
        left_arr[i].company_id=arr[left+i].company_id;
        left_arr[i].price=arr[left+i].price;
    }
    for(long long int i=0;i<mid2;i++)
    {
        right_arr[i].company_id=arr[mid+i+1].company_id;
        right_arr[i].price=arr[mid+i+1].price;
    }
    long long int left_index=0 , right_index=0, arr_index=left;
    while(left_index < mid1 and right_index < mid2)
    {
        if(left_arr[left_index].company_id > right_arr[right_index].company_id)
        {
            arr[arr_index].company_id=right_arr[right_index].company_id;
            arr[arr_index].price=right_arr[right_index].price;
            right_index++;
            arr_index++;
        }
        else
        {
            arr[arr_index].company_id=left_arr[left_index].company_id;
            arr[arr_index].price=left_arr[left_index].price;
            left_index++;
            arr_index++;
        }
    }
        while(right_index < mid2)
        {
            arr[arr_index].company_id=right_arr[right_index].company_id;
            arr[arr_index].price=right_arr[right_index].price;
            right_index++;
            arr_index++;
        }
        while(left_index < mid1)
        {
            arr[arr_index].company_id=left_arr[left_index].company_id;
            arr[arr_index].price=left_arr[left_index].price;
            left_index++;
            arr_index++;
        }

}
void merge_sort(term arr[],long long int left,long long int right)
{
    if (left <right)
    {
        long long int mid=(left+right)/2;
        merge_sort(arr,left,mid);
        merge_sort(arr,mid+1,right);
        merge(arr,left,mid,right);
    }
}
//rotation to maintain avl property
node *rotate(node *A,node *parent)
{
    node *B;
    B=to_find_B(A);
    if(height(A) > 1 and (height(B)==1 or height(B)==0 ))//rotate ll
    {
        parent_linking(parent,A,B);
        A->left_link=B->right_link;
        B->right_link=A;
        height_modification(A,A->left_link);
        height_modification(B,A);
        height_modification(parent,B);
        return B;
    }
    else if(height(A) < -1 and (height(B)==-1 or height(B)==0))//rotate rr
    {
        parent_linking(parent,A,B);
        A->right_link=B->left_link;
        B->left_link=A;
        height_modification(A,A->right_link);
        height_modification(B,A);
        height_modification(parent,B);
        return B;
    }
    else if(height(A) > 1 and height(B)==-1)//rotatelr
    {
        node *C;
        C=B->right_link;
        parent_linking(parent,A,C);
        B->right_link=C->left_link;
        A->left_link=C->right_link;
        C->left_link=B;
        C->right_link=A;
        height_modification(B,B->right_link);
        height_modification(A,A->left_link);
        height_modification(C,B);
        height_modification(C,A);
        height_modification(parent,C);
        return C;
    }
    else
    {
        node *C;
        C=B->left_link;
        parent_linking(parent,A,C);
        B->left_link=C->right_link;
        A->right_link=C->left_link;
        C->right_link=B;
        C->left_link=A;
        height_modification(B,B->left_link);
        height_modification(A,A->right_link);
        height_modification(C,B);
        height_modification(C,A);
        height_modification(parent,C);
        return C;
    }

}
//register company on leaf and balance the tree
int recursion_for_insertion(node *temp)
{
    if(temp->right_link==NULL and temp->company_id < n->company_id)
    {
        temp->right_link=n;
        temp->right_height++;
        n1=temp;
        return 0;
    }
    else if(temp->left_link==NULL and temp->company_id > n->company_id)
    {
        temp->left_link=n;
        temp->left_height++;
        n1=temp;
        return 0;
    }
    else
    {
        if(temp->company_id < n->company_id )
        {
            recursion_for_insertion(temp->right_link);
            height_modification(n1,n1->right_link);
            height_modification(n1,n1->left_link);
            if(height(n1)>1 or height(n1)<-1)
            {
                rotate(n1,temp);
            }
            n1=temp;
        }
        else
        {
            recursion_for_insertion(temp->left_link);
            height_modification(n1,n1->right_link);
            height_modification(n1,n1->left_link);
            if(height(n1)>1 or height(n1)<-1)
            {
                rotate(n1,temp);
            }
            n1=temp;
        }
    }
    return 0;
}
void register_company(long long int company_id,long long int price,long long int no_of_initial_data)
{
    n=new node;
    n->company_id=company_id;
    n->price=price;
    n->left_height=0;
    n->right_height=0;
    n->published_price=price;
    if(no_of_initial_data>0 and start->company_id!=-1)
    {
        recursion_for_insertion(temp);
        height_modification(temp,temp->right_link);
        height_modification(temp,temp->left_link);
        if(height(temp)>1 or height(temp)<-1)
        {
            start=rotate(temp,temp);
        }
    }
    else
    {
        start=n;
    }
}
//to find by which i can remove the node which has to delete
//i have gone to first right of deleting node  and last left node of that right node
int gotonull(node *temp)
{
    if(temp->left_link==NULL)
    {
        if(n6!=n5)
        {
            n6->left_link=temp->right_link;
            height_modification(n6,n6->left_link);
        }
        parent_linking(n2,n5,temp);
        if(temp!=n5->left_link)temp->left_link=n5->left_link;
        if(temp!=n5->right_link)temp->right_link=n5->right_link;
        height_modification(temp,temp->left_link);
        height_modification(temp,temp->right_link);
        n5=temp;
        n3=goodnode();
        return 0;
    }
    else
    {
        n6=temp;
        gotonull(temp->left_link);
        height_modification(n3,n3->right_link);
        height_modification(n3,n3->left_link);
        if(height(n3)>1 or height(n3)<-1)
        {
            rotate(n3,temp);
        }
        n3=temp;
    }
 return 0;
}
//finding the node to delete and balance the avl if get distorted
int deregister_company(long long int company_id,node *temp)
{
    if(temp->company_id ==company_id)
    {
        if(temp->right_link!=NULL)
        {
            n5=temp;
            n6=temp;
            temp=temp->right_link;
            gotonull(temp);
            height_modification(temp,temp->right_link);
            height_modification(temp,temp->left_link);
            if(n5!=temp)
            {
                if(height(temp)>1 or height(temp)<-1)
                {
                    rotate(temp,n5);
                }
            }
            n3=n5;
        }
        else
        {
            parent_linking(n2,temp,temp->left_link);
            height_modification(n2,n2->right_link);
            height_modification(n2,n2->left_link);
            n3=goodnode();
        }
        return 0;
    }
    else if(temp->company_id < company_id and temp->right_link!=NULL)
    {
        n2=temp;
        deregister_company(company_id,temp->right_link);
        height_modification(n3,n3->right_link);
        height_modification(n3,n3->left_link);
        if(height(n3)>1 or height(n3)<-1)
        {
            rotate(n3,temp);
        }
        n3=temp;
    }
    else if(temp->company_id > company_id and temp->left_link!=NULL)
    {
        n2=temp;
        deregister_company(company_id,temp->left_link);
        height_modification(n3,n3->right_link);
        height_modification(n3,n3->left_link);
        if(height(n3)>1 or height(n3)<-1)
        {
            rotate(n3,temp);
        }
        n3=temp;
    }
    else
    {
        n3=goodnode();
        return 0;
    }
    return 0;
}






int main()
{
    long long int no_of_initial_data,operation_code,no_of_operation,threshold_value,company_id,price,x,y;
    cin>>no_of_initial_data;
    if(no_of_initial_data>0)
    {
        term arr[no_of_initial_data];
        for(long long int i=0;i<no_of_initial_data;i++)
        {
            cin>>arr[i].company_id;
            cin>>arr[i].price;
        }
        merge_sort(arr,0,no_of_initial_data-1);
        first_node(arr,no_of_initial_data-1);
        temp=start;
        avltree_of_initial_stock(arr,0,(no_of_initial_data-1)/2,no_of_initial_data-1,no_of_initial_data,temp,temp,temp,temp);
        temp=start;
    }
    cin>>no_of_operation>>threshold_value;
    for(long long int i=0;i<no_of_operation;i++)
    {
        cin>>operation_code;
        if(operation_code==1)
        {
            cin>>company_id>>price;
            cout<<company_id<<" "<<price<<endl;
            register_company(company_id,price,no_of_initial_data);
            temp=start;
            no_of_initial_data=1;
        }
        else if(operation_code==2)
        {
            cin>>company_id;
            if(no_of_initial_data>0)
            {
                if(start->company_id==company_id)
                {
                    n2=temp;
                    if(start->left_link==NULL and start->right_link==NULL)
                    {
                        start->company_id=-1;
                    }
                    else if(start->left_link==NULL)
                    {
                        start=start->right_link;
                    }
                    else if(start->right_link==NULL)
                    {
                        start=start->left_link;
                    }
                    else
                    {
                        deregister_company(company_id,temp);
                        height_modification(n5,n5->right_link);
                        height_modification(n5,n5->left_link);
                        if(height(n5)>1 or height(n5)<-1)
                        {
                            start=rotate(n5,n5);
                        }
                        start=n5;
                    }
                }
                else
                {
                    n2=temp;
                    deregister_company(company_id,temp);
                    height_modification(temp,temp->right_link);
                    height_modification(temp,temp->left_link);
                    if(height(temp)>1 or height(temp)<-1)
                    {
                        start=rotate(temp,temp);
                    }
                }
                temp=start;
            }
        }
        else if(operation_code==3)
        {
            cin>>company_id>>price;
            if(no_of_initial_data>0 and start->company_id!=-1)
            {
                temp=traverse(company_id);
                if(temp->company_id ==company_id)
                {
                    temp->price=price;
                if(temp->price-temp->published_price>threshold_value or temp->published_price-temp->price>threshold_value)
                {
                    temp->published_price=price;
                    cout<<temp->company_id<<" "<<temp->price<<endl;
                }
                }
                temp=start;
            }
        }
        else if(operation_code==4)
        {
            cin>>company_id;
            scanf("%lld : %lld",&x,&y);
            temp=traverse(company_id);
            if(no_of_initial_data>0 and start->company_id!=-1)
            {
                if(temp->company_id ==company_id)
                {
                    temp->price=temp->price*y/x;
                    temp->published_price=temp->price;
                    cout<<temp->company_id<<" "<<temp->price<<endl;
                }
                temp=start;
            }
        }
    }
    // print_tree(temp);////////////////////////////
    //temp=start;
}
