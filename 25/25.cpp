#include "../lib.hpp"

enum op_t {
    op_cpy,
    op_inc,
    op_dec,
    op_jnz,
    op_tgl,
    op_out
};

unordered_map<string, op_t> op_name = {
    { "cpy", op_cpy },
    { "inc", op_inc },
    { "dec", op_dec },
    { "jnz", op_jnz },
    { "tgl", op_tgl },
    { "out", op_out }
};

static int32_t regs[4] = { 182, 0, 0, 0 };
static int32_t reg_jmp, reg_tgl;

struct val_t {
    union {
        int32_t *reg;
        int32_t im;
    };
    bool is_im;

    int32_t& get() { return is_im ? im : *reg; }

    val_t(const string &v) {
        if (isdigit(v[0]) || v[0] == '-') {
            im = stoi(v);
            is_im = true;
        }
        else {
            reg = &(regs[v[0] - 'a']);
            is_im = false;
        }
    }

    val_t() {}
};

struct cmd_t {
    op_t op;
    val_t arg1;
    val_t arg2;
};

unordered_map<op_t, function<void(cmd_t&)>> ops = {
    { op_cpy, [](cmd_t &c) { if (!c.arg2.is_im) c.arg2.get() = c.arg1.get(); } },
    { op_inc, [](cmd_t &c) { c.arg1.get()++; } },
    { op_dec, [](cmd_t &c) { c.arg1.get()--; } },
    { op_jnz, [](cmd_t &c) { if (c.arg1.get()) reg_jmp = c.arg2.get(); } },
    { op_tgl, [](cmd_t &c) { reg_tgl = c.arg1.get(); } },
    { op_out, [](cmd_t &c) { cout << ' ' << c.arg1.get(); } }
};

unordered_map<op_t, function<void(cmd_t&)>> tops = {
    { op_cpy, ops[op_jnz] },
    { op_inc, ops[op_dec] },
    { op_dec, ops[op_inc] },
    { op_jnz, ops[op_cpy] },
    { op_tgl, ops[op_inc] },
    { op_out, ops[op_out] }
};

int main() {
    const regex linerex2("(.*) (.*) (.*)");
    const regex linerex1("(.*) (.*)");
    vector<cmd_t> program;
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        cmd_t cmd;
        smatch linematch;
        if (regex_match(s, linematch, linerex2) && linematch.size() == 4) {
            cmd.op = op_name[linematch[1].str()];
            cmd.arg1 = val_t(linematch[2].str());
            cmd.arg2 = val_t(linematch[3].str());
        }
        else if (regex_match(s, linematch, linerex1) && linematch.size() == 3) {
            cmd.op = op_name[linematch[1].str()];
            cmd.arg1 = val_t(linematch[2].str());
        }
        program.push_back(cmd);
    }

    int32_t ptr = 0;
    vector<bool> toggled(program.size(), false);
    while (ptr < program.size()) {
        reg_jmp = 1;
        reg_tgl = -1000;

        cmd_t &cmd = program[ptr];
        if (toggled[ptr])
            tops[cmd.op](cmd);
        else {
            ops[cmd.op](cmd);
            if (cmd.op == op_tgl && ptr + reg_tgl >= 0 && ptr + reg_tgl < program.size())
                toggled[ptr + reg_tgl] = true;
        }

        ptr += reg_jmp;
    }

    cout << regs[0] << endl;

    return 0;
}

