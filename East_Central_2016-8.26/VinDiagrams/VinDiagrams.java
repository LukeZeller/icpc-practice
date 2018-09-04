import java.util.ArrayList;
import java.util.Objects;
import java.util.Scanner;

public class Main {
    static class Solver {
        int R;
        int C;

        char[][] map;

        char[][] marker;
        char[][] flood;

        int ax;
        int ay;

        int bx;
        int by;

        Solver() {
            Scanner sc = new Scanner(System.in);
            while (sc.hasNextInt()) {
                String[] split = sc.nextLine().split(" ");
                R = Integer.parseInt(split[0]);
                C = Integer.parseInt(split[1]);
                map = new char[C][R];
                marker = new char[C][R];
                flood = new char[C][R];
                for (int i = 0 ; i < R; i ++ ) {
                    String l = sc.nextLine();
                    for (int j = 0; j < l.length(); j ++) {
                        char c = l.charAt(j);
                        map[j][i] = c;
                        if (c == 'A') {
                            ax = j;
                            ay = i;
                        }

                        if (c == 'B') {
                            bx = j;
                            by = i;
                        }
                    }
                }

                crawl(ax, ay, 0, (char) 0b01);
                crawl(bx, by, 0, (char) 0b10);
                selectValidPoint(ax, ay, (char) 0b01);
                floodFill(vp_x,vp_y,(char) 0b01);
                selectValidPoint(bx, by, (char) 0b10);
                floodFill(vp_x,vp_y,(char) 0b10);

                int both = 0;
                int onlyA = 0;
                int onlyB = 0;

                for (int y = 0; y < R; y ++) {
                    for (int x = 0; x < C; x ++) {
                        char c = flood[x][y];
                        if (c == 0b01 && map[x][y] == '.') {
                            onlyA ++;
                        } else if (c == 0b10 && map[x][y] == '.') {
                            onlyB ++;
                        } else if (c == 0b11) {
                            both ++;
                        }
                    }
                }

                System.out.println(String.format("%d %d %d", onlyA, onlyB, both));
            }
        }

        int vp_x;
        int vp_y;

        void floodFill(int x, int y, char mask) {
            flood[x][y] |= mask;
            int[][] dirs = {
                    {x+1,y},
                    {x-1,y},
                    {x,y+1},
                    {x,y-1}
            };
            for (int i = 0; i < 4; i ++) {
                int nx = dirs[i][0];
                int ny = dirs[i][1];
                if (passable(nx,ny,mask) && (flood[nx][ny] & mask) == 0) {
                    floodFill(nx, ny, mask);
                }
            }
        }

        void selectValidPoint(int x, int y, char mask) {
            int[][] list = {{x+1,y},{x-1,y},{x,y+1},{x,y-1},{x+1,y+1},{x+1,y-1},{x-1,y+1},{x-1,y-1}};
            for (int i = 0; i < 8; i ++) {
                if(validPoint(list[i][0], list[i][1], mask)) {
                    vp_x = list[i][0];
                    vp_y = list[i][1];
                    break;
                }
            }
        }


        boolean isWall(int x, int y) {
            if (x < 0 || x >= C) return false;
            if (y < 0 || y >= R) return false;
            if (map[x][y] == '.') return false;
            return true;
        }

        boolean surrounded(int ox, int oy, char mask) {
            int cnt = 0;
            for (int x = ox + 1; x < C; x ++) {
                if (isWall(x, oy) && ((marker[x][oy] & mask) != 0)) {
                    cnt++;
                    break;
                }
            }

            for (int x = 0; x < ox; x ++) {
                if (isWall(x, oy) && (marker[x][oy] & mask) != 0){
                    cnt++;
                    break;
                }
            }

            for (int y = oy + 1; y < R; y ++) {
                if (isWall(ox, y) && (marker[ox][y] & mask) != 0) {
                    cnt++;
                    break;
                }
            }

            for (int y = 0; y < oy; y ++) {
                if (isWall(ox, y) && (marker[ox][y] & mask) != 0) {
                    cnt++;
                    break;
                }
            }

            return cnt == 4;
        }

        boolean passable(int x, int y, char mask) {
            if (x < 0 || x >= C) return false;
            if (y < 0 || y >= R) return false;
            return (marker[x][y] & mask) == 0;
        }

        boolean validPoint(int x, int y, char mask) {
            return passable(x, y, mask) && surrounded(x, y, mask);
        }

        boolean isIntersection(int x, int y) {
            return isWall(x, y) && isWall(x+1,y)&&isWall(x-1,y)
                    && isWall(x, y + 1) && isWall(x, y -1);
        }

        // A : 0b01
        // B : 0b10

        void crawl(int x, int y, int dir, char mask) {
            marker[x][y] |= mask;
            if (dir == 0) {
                if (isWall(x, y - 1)) {
                    crawl(x, y - 1, 2, mask);
                } else if (isWall(x, y + 1)) {
                    crawl(x, y + 1, 8, mask);
                } else if (isWall(x - 1, y)) {
                    crawl(x - 1, y, 4, mask);
                } else if (isWall(x + 1, y)) {
                    crawl(x + 1, y, 6, mask);
                }
            } else {
                if (isIntersection(x, y)) {
                    int nx, ny;
                    nx = x;
                    ny = y;
                    switch (dir) {
                        case 2:
                           ny--;
                           break;
                        case 8:
                            ny++;
                            break;
                        case 4:
                            nx--;
                            break;
                        case 6:
                            nx++;
                            break;
                    }
                    crawl(nx, ny, dir, mask);
                } else {
                    if (isWall(x+1,y) && ((marker[x+1][y] & mask) == 0)) {
                        crawl(x+1,y,6,mask);
                    } else if (isWall(x-1,y) && ((marker[x-1][y] & mask) == 0)) {
                        crawl(x-1,y,4,mask);
                    } else if (isWall(x,y+1) && ((marker[x][y+1] & mask) == 0)) {
                        crawl(x,y+1,8,mask);
                    } else if (isWall(x,y-1) && ((marker[x][y-1] & mask) == 0)) {
                        crawl(x,y-1,2,mask);
                    } else {
                        return;
                    }
                }
            }
        }
    }

    public static void main(String[] args) {
        new Solver();
    }

}
