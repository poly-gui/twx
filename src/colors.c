#include "colors.h"
#include "strutil.h"
#include "twx/twx.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define COLOR_NAME_SLATE 274523902
#define COLOR_NAME_GRAY 2090302584
#define COLOR_NAME_ZINC 2090975993
#define COLOR_NAME_NEUTRAL 191201440
#define COLOR_NAME_STONE 274826446
#define COLOR_NAME_RED 193504576
#define COLOR_NAME_ORANGE 319921761
#define COLOR_NAME_AMBER 253213868
#define COLOR_NAME_YELLOW 696252129
#define COLOR_NAME_LIME 2090472844
#define COLOR_NAME_GREEN 260512342
#define COLOR_NAME_EMERALD 1746909983
#define COLOR_NAME_TEAL 2090755595
#define COLOR_NAME_CYAN 2090166448
#define COLOR_NAME_SKY 193505884
#define COLOR_NAME_BLUE 2090117005
#define COLOR_NAME_INDIGO 80468095
#define COLOR_NAME_VIOLET 583697112
#define COLOR_NAME_PURPLE 363228189
#define COLOR_NAME_FUCHSIA 3348749384
#define COLOR_NAME_PINK 2090616631
#define COLOR_NAME_ROSE 2090695198

struct ColorEntry {
  int num;
  TwxARGB color;
};

// credit to mel !!!
// https://x.com/vmfunc/status/1805362283859611905

static const struct ColorEntry slate_colors[] = {
    {50, 0xFFF8FAFC},  {100, 0xFFF1F5F9}, {200, 0xFFE2E8F0}, {300, 0xFFCBD5E1},
    {400, 0xFF94A3B8}, {500, 0xFF64748B}, {600, 0xFF475569}, {700, 0xFF334155},
    {800, 0xFF1E293B}, {900, 0xFF0F172A}, {950, 0xFF020617}};

static const struct ColorEntry gray_colors[] = {
    {50, 0xFFF9FAFB},  {100, 0xFFF3F4F6}, {200, 0xFFE5E7EB}, {300, 0xFFD1D5DB},
    {400, 0xFF9CA3AF}, {500, 0xFF6B7280}, {600, 0xFF4B5563}, {700, 0xFF374151},
    {800, 0xFF1F2937}, {900, 0xFF111827}, {950, 0xFF030712}};

static const struct ColorEntry zinc_colors[] = {
    {50, 0xFFFAFAFA},  {100, 0xFFF4F4F5}, {200, 0xFFE4E4E7}, {300, 0xFFD4D4D8},
    {400, 0xFFA1A1AA}, {500, 0xFF71717A}, {600, 0xFF52525B}, {700, 0xFF3F3F46},
    {800, 0xFF27272A}, {900, 0xFF18181B}, {950, 0xFF09090B}};

static const struct ColorEntry neutral_colors[] = {
    {50, 0xFFFAFAFA},  {100, 0xFFF5F5F5}, {200, 0xFFE5E5E5}, {300, 0xFFD4D4D4},
    {400, 0xFFA3A3A3}, {500, 0xFF737373}, {600, 0xFF525252}, {700, 0xFF404040},
    {800, 0xFF262626}, {900, 0xFF171717}, {950, 0xFF0A0A0A}};

static const struct ColorEntry stone_colors[] = {
    {50, 0xFFFAFAF9},  {100, 0xFFF5F5F4}, {200, 0xFFE7E5E4}, {300, 0xFFD6D3D1},
    {400, 0xFFA8A29E}, {500, 0xFF78716C}, {600, 0xFF57534E}, {700, 0xFF44403C},
    {800, 0xFF292524}, {900, 0xFF1C1917}, {950, 0xFF0C0A09}};

static const struct ColorEntry red_colors[] = {
    {50, 0xFFFEF2F2},  {100, 0xFFFEE2E2}, {200, 0xFFFECACA}, {300, 0xFFFCA5A5},
    {400, 0xFFF87171}, {500, 0xFFEF4444}, {600, 0xFFDC2626}, {700, 0xFFB91C1C},
    {800, 0xFF991B1B}, {900, 0xFF7F1D1D}, {950, 0xFF450A0A}};

static const struct ColorEntry orange_colors[] = {
    {50, 0xFFFFF7ED},  {100, 0xFFFFEDD5}, {200, 0xFFFED7AA}, {300, 0xFFFDBA74},
    {400, 0xFFFB923C}, {500, 0xFFF97316}, {600, 0xFFEA580C}, {700, 0xFFC2410C},
    {800, 0xFF9A3412}, {900, 0xFF7C2D12}, {950, 0xFF431407}};

static const struct ColorEntry amber_colors[] = {
    {50, 0xFFFFFBEB},  {100, 0xFFFEF3C7}, {200, 0xFFFDE68A}, {300, 0xFFFCD34D},
    {400, 0xFFFBBF24}, {500, 0xFFF59E0B}, {600, 0xFFD97706}, {700, 0xFFB45309},
    {800, 0xFF92400E}, {900, 0xFF78350F}, {950, 0xFF451A03}};

static const struct ColorEntry yellow_colors[] = {
    {50, 0xFFFEFCE8},  {100, 0xFFFEF9C3}, {200, 0xFFFEF08A}, {300, 0xFFFDE047},
    {400, 0xFFFACC15}, {500, 0xFFEAB308}, {600, 0xFFCA8A04}, {700, 0xFFA16207},
    {800, 0xFF854D0E}, {900, 0xFF713F12}, {950, 0xFF422006}};

static const struct ColorEntry lime_colors[] = {
    {50, 0xFFF7FEE7},  {100, 0xFFECFCCB}, {200, 0xFFD9F99D}, {300, 0xFFBEF264},
    {400, 0xFFA3E635}, {500, 0xFF84CC16}, {600, 0xFF65A30D}, {700, 0xFF4D7C0F},
    {800, 0xFF3F6212}, {900, 0xFF365314}, {950, 0xFF1A2E05}};

static const struct ColorEntry green_colors[] = {
    {50, 0xFFF0FD74},  {100, 0xFFDCFCE7}, {200, 0xFFBBF7D0}, {300, 0xFF86EFAC},
    {400, 0xFF4ADE80}, {500, 0xFF22C55E}, {600, 0xFF16A34A}, {700, 0xFF15803D},
    {800, 0xFF166534}, {900, 0xFF14532D}, {950, 0xFF052E16}};

static const struct ColorEntry emerald_colors[] = {
    {50, 0xFFECFDF5},  {100, 0xFFD1FAE5}, {200, 0xFFA7F3D0}, {300, 0xFF6EE7B7},
    {400, 0xFF34D399}, {500, 0xFF10B981}, {600, 0xFF059669}, {700, 0xFF047857},
    {800, 0xFF065F46}, {900, 0xFF064E3B}, {950, 0xFF022C22}};

static const struct ColorEntry teal_colors[] = {
    {50, 0xFFF0FDFA},  {100, 0xFFCCFBF1}, {200, 0xFF99F6E4}, {300, 0xFF5EEAD4},
    {400, 0xFF2DD4BF}, {500, 0xFF14B8A6}, {600, 0xFF0D9488}, {700, 0xFF0F766E},
    {800, 0xFF115E59}, {900, 0xFF134E4A}, {950, 0xFF042F2E}};

static const struct ColorEntry cyan_colors[] = {
    {50, 0xFFECFEFF},  {100, 0xFFCFFAFE}, {200, 0xFFA5F3FC}, {300, 0xFF67E8F9},
    {400, 0xFF22D3EE}, {500, 0xFF06B6D4}, {600, 0xFF0891B2}, {700, 0xFF0E7490},
    {800, 0xFF155E75}, {900, 0xFF164E63}, {950, 0xFF083344}};

static const struct ColorEntry sky_colors[] = {
    {50, 0xFFF0F9FF},  {100, 0xFFE0F2FE}, {200, 0xFFBAE6FD}, {300, 0xFF7DD3FC},
    {400, 0xFF38BDF8}, {500, 0xFF0EA5E9}, {600, 0xFF0284C7}, {700, 0xFF0369A1},
    {800, 0xFF075985}, {900, 0xFF0C4A6E}, {950, 0xFF082F49}};

static const struct ColorEntry blue_colors[] = {
    {50, 0xFFEFF6FF},  {100, 0xFFDBEAFE}, {200, 0xFFBFDBFE}, {300, 0xFF93C5FD},
    {400, 0xFF60A5FA}, {500, 0xFF3B82F6}, {600, 0xFF2563EB}, {700, 0xFF1D4ED8},
    {800, 0xFF1E40AF}, {900, 0xFF1E3A8A}, {950, 0xFF172554}};

static const struct ColorEntry indigo_colors[] = {
    {50, 0xFFEEF2FF},  {100, 0xFFE0E7FF}, {200, 0xFFBFDBFE}, {300, 0xFFA5B4FC},
    {400, 0xFF818CF8}, {500, 0xFF6366F1}, {600, 0xFF4F46E5}, {700, 0xFF4338CA},
    {800, 0xFF3730A3}, {900, 0xFF312E81}, {950, 0xFF1E1B4B}};

static const struct ColorEntry violet_colors[] = {
    {50, 0xFFF5F3FF},  {100, 0xFFF3E8FF}, {200, 0xFFE9D5FF}, {300, 0xFFC4B5FA},
    {400, 0xFFA78BFA}, {500, 0xFF8B5CF6}, {600, 0xFF7C3AED}, {700, 0xFF6D28D9},
    {800, 0xFF5B21B6}, {900, 0xFF4C1D95}, {950, 0xFF2E1065}};

static const struct ColorEntry purple_colors[] = {
    {50, 0xFFFAF5FF},  {100, 0xFFF3E8FF}, {200, 0xFFE9D5FF}, {300, 0xFFD8B4FE},
    {400, 0xFFC084FC}, {500, 0xFFA855F7}, {600, 0xFF9333EA}, {700, 0xFF7E22CE},
    {800, 0xFF6B21A8}, {900, 0xFF581C87}, {950, 0xFF3B0764}};

static const struct ColorEntry fuchsia_colors[] = {
    {50, 0xFFFDF4FF},  {100, 0xFFFAE8FF}, {200, 0xFFF5D0FE}, {300, 0xFFF0ABFC},
    {400, 0xFFE879F9}, {500, 0xFFD946EF}, {600, 0xFFC026D3}, {700, 0xFFA21CAF},
    {800, 0xFF86198F}, {900, 0xFF701A75}, {950, 0xFF4A044E}};

static const struct ColorEntry pink_colors[] = {
    {50, 0xFFFDF2F8},  {100, 0xFFFCE7F3}, {200, 0xFFFBCFE8}, {300, 0xFFF9A8D4},
    {400, 0xFFF472B6}, {500, 0xFFEC4899}, {600, 0xFFDB2777}, {700, 0xFFBE185D},
    {800, 0xFF9D174D}, {900, 0xFFB31843}, {950, 0xFF500724}};

static const struct ColorEntry rose_colors[] = {
    {50, 0xFFFFF1F2},  {100, 0xFFFFE4E6}, {200, 0xFFFECDD3}, {300, 0xFFFDA4AF},
    {400, 0xFFFB7185}, {500, 0xFFF43F5E}, {600, 0xFFE11D48}, {700, 0xFFBE123C},
    {800, 0xFF9F1239}, {900, 0xFFBB1337}, {950, 0xFF4C0519}};

bool color_by_num(const struct ColorEntry *color_table, const int num,
                  TwxARGB *color) {
  if (color == NULL)
    return false;
  for (int i = 0; i < 11; ++i) {
    if (color_table[i].num == num) {
      *color = color_table[i].color;
      return true;
    }
  }
  return false;
}

bool get_tw_color(const char *color_name, const int color_num, TwxARGB *color) {
  uint32_t hash = strhash(color_name);

  const struct ColorEntry *color_table = NULL;
  switch (hash) {
  case COLOR_NAME_SLATE:
    color_table = slate_colors;
    break;
  case COLOR_NAME_GRAY:
    color_table = gray_colors;
    break;
  case COLOR_NAME_ZINC:
    color_table = zinc_colors;
    break;
  case COLOR_NAME_NEUTRAL:
    color_table = neutral_colors;
    break;
  case COLOR_NAME_STONE:
    color_table = stone_colors;
    break;
  case COLOR_NAME_RED:
    color_table = red_colors;
    break;
  case COLOR_NAME_ORANGE:
    color_table = orange_colors;
    break;
  case COLOR_NAME_AMBER:
    color_table = amber_colors;
    break;
  case COLOR_NAME_YELLOW:
    color_table = yellow_colors;
    break;
  case COLOR_NAME_LIME:
    color_table = lime_colors;
    break;
  case COLOR_NAME_GREEN:
    color_table = green_colors;
    break;
  case COLOR_NAME_EMERALD:
    color_table = emerald_colors;
    break;
  case COLOR_NAME_CYAN:
    color_table = cyan_colors;
    break;
  case COLOR_NAME_SKY:
    color_table = sky_colors;
    break;
  case COLOR_NAME_BLUE:
    color_table = blue_colors;
    break;
  case COLOR_NAME_INDIGO:
    color_table = indigo_colors;
    break;
  case COLOR_NAME_VIOLET:
    color_table = violet_colors;
    break;
  case COLOR_NAME_PURPLE:
    color_table = purple_colors;
    break;
  case COLOR_NAME_FUCHSIA:
    color_table = fuchsia_colors;
    break;
  case COLOR_NAME_PINK:
    color_table = pink_colors;
    break;
  case COLOR_NAME_ROSE:
    color_table = rose_colors;
    break;
  default:
    return false;
  }

  return color_by_num(color_table, color_num, color);
}

bool parse_color_string(const char *color_str, TwxARGB *color) {
  char *hyphen = strchr(color_str, '-');
  if (hyphen == NULL) {
    return NULL;
  }

  const size_t split_i = (size_t)(hyphen - color_str);
  char *color_name = substr(color_str, 0, split_i);
  if (color_name == NULL) {
    return false;
  }

  char *color_num_str = substr(color_str, split_i, strlen(color_str));
  if (color_num_str == NULL) {
    return false;
  }

  int color_num = atoi(color_num_str);
  if (color_num == 0) {
    return 0;
  }

  return get_tw_color(color_name, color_num, color);
}

void parse_bg(const char *class_name, struct TwxStyle *style) {
  parse_color_string(class_name + 3, &style->background_color);
}
