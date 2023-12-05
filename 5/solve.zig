const std = @import("std");
const print = std.debug.print;
const split = std.mem.split;
const parse = std.fmt.parseUnsigned;

var buffer: [256]u8 = undefined;
fn readline() ?[]u8 {
    return std.io.getStdIn().reader().readUntilDelimiterOrEof(&buffer, '\n') catch {
        return null;
    };
}

const Range = struct { from: usize, to: usize };

pub fn main() !void {
    const firstLine = readline().?[7..];
    var seeds: [128]usize = undefined;
    var ranges: [128]Range = undefined;

    var nseeds: usize = 0;
    var it = split(u8, firstLine, " ");
    while (it.next()) |seed| : (nseeds += 1) {
        seeds[nseeds] = try parse(usize, seed, 10);
    }
    var nranges: usize = nseeds / 2;
    for (0..nranges) |i| {
        ranges[i] = Range{ .from = seeds[2 * i], .to = seeds[2 * i] + seeds[2 * i + 1] };
    }

    _ = readline();
    while (readline()) |_| {
        var cseeds = [_]?usize{null} ** 128;
        var cranges = [_]?Range{null} ** 128;

        while (readline()) |line| {
            if (line.len == 0) break;
            it = split(u8, line, " ");
            const target = try parse(usize, it.next().?, 10);
            const from = try parse(usize, it.next().?, 10);
            const to = from + try parse(usize, it.next().?, 10);
            // part 1
            for (0..nseeds) |i| {
                if (from <= seeds[i] and seeds[i] < to) {
                    cseeds[i] = seeds[i] + target - from;
                }
            }
            // part 2
            var i: usize = 0;
            while (i < nranges) : (i += 1) {
                var r = ranges[i];
                // check for interval collisions
                inline for (.{ from, to }) |l| {
                    if (r.from < l and l < r.to) {
                        ranges[i] = Range{ .from = r.from, .to = l };
                        ranges[nranges] = Range{ .from = l, .to = r.to };
                        nranges += 1;
                        r = ranges[i];
                    }
                }
                // transform the intervals
                if (from <= r.from and r.to <= to) {
                    cranges[i] = Range{ .from = r.from + target - from, .to = r.to + target - from };
                }
            }
        }
        for (0..nseeds) |i| seeds[i] = cseeds[i] orelse seeds[i];
        for (0..nranges) |i| ranges[i] = cranges[i] orelse ranges[i];
    }
    var ans1: ?usize = null;
    var ans2: ?usize = null;
    for (0..nseeds) |i| if (ans1 == null or ans1.? > seeds[i]) {
        ans1 = seeds[i];
    };
    for (0..nranges) |i| if (ans2 == null or ans2.? > ranges[i].from) {
        ans2 = ranges[i].from;
    };
    print("part 1: {}\n", .{ans1.?});
    print("part 2: {}\n", .{ans2.?});
}
