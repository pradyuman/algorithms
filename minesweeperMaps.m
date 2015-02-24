%Created minesweeper maps
clear   % clears all variables and functions from the workspace
clc     % clears the command window

% --- INPUTS ---
%Will remove the outer ring of the matrix for final output so that extra work
%is not needed for corners/edges
m = randi([4,10]); %x axis, m-2 = size
n = randi([4,10]); % y axis, n-2 = size

%Can take input from a user if wanted
%To use: Uncomment the next 4 lines of code and comment out the code before this.

%m = input('Enter m: ');
%n = input('Enter n: ');

%m = m + 2;
%n = n + 2;

if(m < 2 || n < 2)
    fprintf('ERROR: Invalid input. m and n have to be greater than or equal to 2.\n')
else
    initial_mine = floor(2*rand(m,n));
    initial_mine(:,1) = 0;
    initial_mine(1,:) = 0;
    initial_mine(:,n) = 0;
    initial_mine(m,:) = 0;

    % --- CALCULATIONS ---
    counting_mine = 10*initial_mine;

    %Calculating middle mine values
    for i = 2:(m-1) %x axis for counting_mine
        for j = 2:(n-1) % y axis for counting_mine
            if (initial_mine(i,j) == 1)
                for a = -1:1 %going around the mine on the x-axis
                    for b = -1:1 %going around the mine on the y-axis
                        if(initial_mine(i+a,j+b) ~= 1)
                            counting_mine(i+a,j+b) = counting_mine(i+a,j+b) + 1;
                        end
                    end
                end
            end
        end
    end

    %Removing outer ring of values
    counting_mine(:,1) = [];
    counting_mine(1,:) = [];
    counting_mine(:,n-1) = [];
    counting_mine(m-1,:) = [];
    % --- OUTPUTS ----
    counting_mine
end