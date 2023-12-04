const std = @import("std");
const parse = std.fmt.parseUnsigned;

fn solve(line: []const u8) ![2]u32 {
    const start = std.mem.indexOf(u8, line, ":").? + 1;
    var it = std.mem.split(u8, line[start..], " ");
    var winning: [256]bool = undefined;
    while(it.next()) |v| if (v.len > 0){
        const n = parse(u8, v, 10) catch { break; };
        winning[n] = true;
    };
    var ans1: u32 = 1;
    var ans2: u32 = 0;
    while(it.next()) |v| if (v.len > 0){
        if(winning[try parse(u8, v, 10)]) {
            ans1 *= 2;
            ans2 += 1;
        }
    };
    return [_]u32{ans1/2, ans2};
}

pub fn main() !void {
    const stdin = std.io.getStdIn().reader();
    var buffer: [256]u8 = undefined;

    var sum1: u32 = 0;
    var sum2: u32 = 0;
    var copies: [256]u32 = undefined;
    for (0..256) |i| copies[i] = 1;
    var i: usize = 0;
    while (try stdin.readUntilDelimiterOrEof(&buffer, '\n')) |line|: (i+=1) {
        var res = try solve(line);
        sum1 += res[0];
        sum2 += copies[i];
        for (0..res[1]) |j| copies[i + j + 1] += copies[i];
    }
    std.debug.print("part 1: {}\n", .{sum1});
    std.debug.print("part 2: {}\n", .{sum2});
}
